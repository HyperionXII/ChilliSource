//
//  TapGesture.h
//  Chilli Source
//  Created by Ian Copland on 17/09/2014.
//
//  The MIT License (MIT)
//
//  Copyright (c) 2014 Tag Games Limited
//
//  Permission is hereby granted, free of charge, to any person obtaining a copy
//  of this software and associated documentation files (the "Software"), to deal
//  in the Software without restriction, including without limitation the rights
//  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//  copies of the Software, and to permit persons to whom the Software is
//  furnished to do so, subject to the following conditions:
//
//  The above copyright notice and this permission notice shall be included in
//  all copies or substantial portions of the Software.
//
//  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
//  THE SOFTWARE.
//

#ifndef _CHILLISOURCE_INPUT_GESTURE_TAPGESTURE_H_
#define _CHILLISOURCE_INPUT_GESTURE_TAPGESTURE_H_

#include <ChilliSource/ChilliSource.h>
#include <ChilliSource/Core/Event/Event.h>
#include <ChilliSource/Input/Gesture/Gesture.h>

#include <functional>

namespace ChilliSource
{
    namespace Input
    {
        //----------------------------------------------------------
        /// A gesture for receiving tap inpur events. Allows for
        /// multi-tap events like double and triple tap.
        ///
        /// @author Ian Copland
        //----------------------------------------------------------
        class TapGesture final : public Gesture
        {
        public:
            CS_DECLARE_NAMEDTYPE(TapGesture);
            //----------------------------------------------------
            /// A delegate called when a tap gesture is activated.
            ///
            /// @author Ian Copland
            //----------------------------------------------------
            using ActivatedDelegate = std::function<void(const TapGesture*)>;
            //----------------------------------------------------
            /// Constructor. Constructs the tap gesture with the
            /// given settings.
            ///
            /// @author Ian Copland
            ///
            /// @param The number of taps required to activate
            /// this tap gesture. Defaults to 1.
            /// @param The number of pointers that should be
            /// down per tap.
            /// @param The maximum time a pointer can be down
            /// for it to be considered a tap. Defaults to 0.15
            /// seconds.
            /// @param The maximum time between each tap before
            /// the tap counter will reset. Defaults to 0.25
            /// seconds.
            //----------------------------------------------------
			TapGesture(u32 in_numTaps = 1, u32 in_numPointers = 1, f32 in_maxTimeForTap = 0.15f, f32 in_maxTimeBetweenTaps = 0.25f);
            //----------------------------------------------------
            /// Queries whether or not this implements the gesture
            /// interface with the given Id.
            ///
            /// @author Ian Copland
            ///
            /// @param The gesture interface Id.
            ///
            /// @return Whether or not the gesture inteface is
            /// implemented.
            //----------------------------------------------------
			bool IsA(Core::InterfaceIDType in_gestureInterfaceId) const override;
            //----------------------------------------------------
            /// @author Ian Copland
            ///
            /// @return The number of taps required by this Tap
            /// Gesture before it will activate.
            //----------------------------------------------------
            u32 GetNumTaps() const;
            //----------------------------------------------------
            /// @author Ian Copland
            ///
            /// @return The number of pointers required by this Tap
            /// Gesture for each tap.
            //----------------------------------------------------
            u32 GetNumPointers() const;
            //----------------------------------------------------
            /// @author Ian Copland
            ///
            /// @return The maximum time a pointer can be down for
            /// the gesture to consider it a tap.
            //----------------------------------------------------
            f32 GetMaxTimeForTap() const;
            //----------------------------------------------------
            /// @author Ian Copland
            ///
            /// @return The maximum time between taps before the
            /// tap counter is reset.
            //----------------------------------------------------
            f32 GetMaxTimeBetweenTaps() const;
            //----------------------------------------------------
            /// @author Ian Copland
            ///
            /// @return An event that can be used to list for
            /// ocurrances of the gesture.
            //----------------------------------------------------
            Core::IConnectableEvent<ActivatedDelegate>& GetActivatedEvent();
        private:
            //----------------------------------------------------
            /// Information on the initial state of a single
            /// pointer within a tap.
            ///
            /// @author Ian Copland
            //----------------------------------------------------
            struct PointerInfo final
            {
                Core::Vector2 m_initialPosition;
                Pointer::Id m_pointerId;
            };
            //----------------------------------------------------
            /// Information on a single tap.
            ///
            /// @author Ian Copland
            //----------------------------------------------------
            struct TapInfo final
            {
                std::vector<PointerInfo> m_pointers;
                f64 m_startTimestamp;
            };
            //--------------------------------------------------------
            /// Called when a pointer down event occurs.
            ///
            /// @author Ian Copland
            ///
            /// @param The pointer.
            /// @param The timestamp of the event.
            /// @param The press type.
            /// @param The filter, allowing exclusion from the filtered
            /// input event.
            //--------------------------------------------------------
            void OnPointerDown(const Pointer& in_pointer, f64 in_timestamp, Pointer::InputType in_inputType, Filter& in_filter) override;
            //--------------------------------------------------------
            /// Called when a pointer moved event occurs.
            ///
            /// @author Ian Copland
            ///
            /// @param The pointer
            /// @param The timestamp of the event.
            /// @param The filter, allowing exclusion from the filtered
            /// input event.
            //--------------------------------------------------------
            void OnPointerMoved(const Pointer& in_pointer, f64 in_timestamp, Filter& in_filter) override;
            //--------------------------------------------------------
            /// Called when a pointer up event occurs.
            ///
            /// @author Ian Copland
            ///
            /// @param The pointer
            /// @param The timestamp of the event.
            /// @param The press type.
            /// @param The filter, allowing exclusion from the filtered
            /// input event.
            //--------------------------------------------------------
            void OnPointerUp(const Pointer& in_pointer, f64 in_timestamp, Pointer::InputType in_inputType, Filter& in_filter) override;
            
            u32 m_numTaps;
            u32 m_numPointers;
            f32 m_maxTimeForTap;
            f32 m_maxTimeBetweenTaps;
            Core::Event<ActivatedDelegate> m_activatedEvent;
            
            std::vector<TapInfo> m_activeTaps;
        };
    }
}

#endif
