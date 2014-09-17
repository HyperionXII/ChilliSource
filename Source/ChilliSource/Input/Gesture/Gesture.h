//
//  Gesture.h
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

#ifndef _CHILLISOURCE_INPUT_GESTURES_GESTURE_H_
#define _CHILLISOURCE_INPUT_GESTURES_GESTURE_H_

#include <ChilliSource/ChilliSource.h>
#include <ChilliSource/Core/Base/QueryableInterface.h>
#include <ChilliSource/Input/Pointer/Pointer.h>

namespace ChilliSource
{
    namespace Input
    {
        //------------------------------------------------------------
        /// The base class for all input gestures that can be registered
        /// with the gesture system.
        ///
        /// @author Ian Copland
        //------------------------------------------------------------
        class Gesture : public Core::QueryableInterface
        {
        public:
            CS_DECLARE_NAMEDTYPE(Gesture);
            CS_DECLARE_NOCOPY(Gesture);
            //-------------------------------------------------------
            /// Destructor
            ///
            /// @author Ian Copland
            //-------------------------------------------------------
            virtual ~Gesture() {};
            
        protected:
            //-------------------------------------------------------
            /// Protected default constructor
            ///
            /// @author Ian Copland
            //-------------------------------------------------------
            Gesture() = default;
            //-------------------------------------------------------
            /// @author Ian Copland
            ///
            /// @return The owning gesture system. Can be null.
            //-------------------------------------------------------
            GestureSystem* GetGestureSystem() const;
            //--------------------------------------------------------
            /// A method that can optionally be implemented by the
            /// implementing class to receive pointer down events.
            ///
            /// @author Ian Copland
            ///
            /// @param The pointer.
            /// @param The timestamp of the event.
            /// @param The press type.
            /// @param The filter, allowing exclusion from the filtered
            /// input event.
            //--------------------------------------------------------
            virtual void OnPointerDown(const Pointer& in_pointer, f64 in_timestamp, Pointer::InputType in_inputType, Filter& in_filter) {};
            //--------------------------------------------------------
            /// A method that can optionally be implemented by the
            /// implementing class to receive pointer moved events.
            ///
            /// @author Ian Copland
            ///
            /// @param The pointer
            /// @param The timestamp of the event.
            /// @param The filter, allowing exclusion from the filtered
            /// input event.
            //--------------------------------------------------------
            virtual void OnPointerMoved(const Pointer& in_pointer, f64 in_timestamp, Filter& in_filter) {};
            //--------------------------------------------------------
            /// A method that can optionally be implemented by the
            /// implementing class to receive pointer up events.
            ///
            /// @author Ian Copland
            ///
            /// @param The pointer
            /// @param The timestamp of the event.
            /// @param The press type.
            /// @param The filter, allowing exclusion from the filtered
            /// input event.
            //--------------------------------------------------------
            virtual void OnPointerUp(const Pointer& in_pointer, f64 in_timestamp, Pointer::InputType in_inputType, Filter& in_filter) {};
            //--------------------------------------------------------
            /// A method that can optionally be implemented by the
            /// implementing class to receive pointer scrolled events.
            ///
            /// @author Ian Copland
            ///
            /// @param The pointer
            /// @param The timestamp of the event.
            /// @param The scroll vector (x, y delta)
            /// @param The filter, allowing exclusion from the filtered
            /// input event.
            //--------------------------------------------------------
            virtual void OnPointerScrolled(const Pointer& in_pointer, f64 in_timestamp, const Core::Vector2& in_delta, Filter& in_filter) {};
            
        private:
            friend class GestureSystem;
            //-------------------------------------------------------
            /// Will be called by the gesture system when this is
            /// added to it.
            ///
            /// @author Ian Copland
            ///
            /// @param The gesture system. Can be null if removing
            /// from a gesture system.
            //-------------------------------------------------------
            void SetGestureSystem(GestureSystem* in_gestureSystem);
            
            GestureSystem* m_gestureSystem = nullptr;
        };
    }
}

#endif
