//
//  TextEntry.h
//  Chilli Source
//  Created by Scott Downie on 08/07/2014
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

#ifndef _CHILLISOURCE_INPUT_TEXTENTRY_TEXTENTRY_H_
#define _CHILLISOURCE_INPUT_TEXTENTRY_TEXTENTRY_H_

#include <ChilliSource/ChilliSource.h>

#include <functional>

namespace ChilliSource
{
	namespace Input
	{
        //---------------------------------------------------------------
        /// A system for receiving textual from both virtual and hardware
        /// keyboards depending on the platform.
        ///
        /// @author S Downie
        //---------------------------------------------------------------
		class TextEntry
        {
        public:
            //-------------------------------------------------------
            /// An enum describing the different types of keyboard.
            ///
            /// @author S Downie
            //-------------------------------------------------------
            enum class Type
            {
                k_text,
                k_numeric
            };
            //-------------------------------------------------------
            /// An enum describing the various methods of keyboard
            /// capitalisation that can be used.
            ///
            ///  - None: will not capitalise any thing.
            ///  - Words: will capitalise the first letter
            ///	   of each word.
            ///  - Sentences: will capitalise the first letter
            ///	   of each sentence.
            ///  - All: will capitalise every letter.
            ///
            /// @author Ian Copland
            //-------------------------------------------------------
            enum class Capitalisation
            {
                k_none,
                k_words,
                k_sentences,
                k_all
            };
            //-------------------------------------------------------
            /// A delegate used for recieving text input events.
            ///
            /// @param The new updated version of the text.
            /// @param [Out] Whether or not the change to the text
            /// has been rejected.
            ///
            /// @author S Downie
            //-------------------------------------------------------
            typedef std::function<bool(const std::string&)> TextBufferChangedDelegate;
            //-------------------------------------------------------
            /// Factory method from creating a new platform specific
            /// instance of the keyboard system.
            ///
            /// @author Ian Copland
            ///
            /// @return The new instance of the system.
            //-------------------------------------------------------
			static TextEntryUPtr Create();
            //-------------------------------------------------------
            /// Sets whether or not the text input is currently
            /// enabled or disabled. If the keyboard is virtual, it
            /// will be shown or hidden when enabled or disabled.
            ///
            /// @author S Downie
            //-------------------------------------------------------
			virtual void SetTextInputEnabled(bool in_enabled) = 0;
            //-------------------------------------------------------
            /// @author S Downie
            ///
            /// @return Whether or not text input is currently
            /// enabled.
            //-------------------------------------------------------
			virtual bool IsTextInputEnabled() const = 0;
            //-------------------------------------------------------
            /// @author S Downie
            ///
            /// @return The current text input buffer (UTF-8).
            //-------------------------------------------------------
			virtual const std::string& GetTextBuffer() const = 0;
            //-------------------------------------------------------
            /// @author S Downie
            ///
            /// @param The new text input buffer (UTF-8).
            //-------------------------------------------------------
            virtual void SetTextBuffer(const std::string& in_text) = 0;
            //-------------------------------------------------------
            /// Sets the type of keyboard to display if using a
            /// virtual keyboard. This must be set prior to the keyboard
            /// being displayed. Note that this is only a suggestion
            /// and the virtual keyboard implementation may choose to
            /// ignore it.
            ///
            /// @author Ian Copland
            ///
            /// @param The keyboard type
            //-------------------------------------------------------
            virtual void SetType(Type in_type) = 0;
            //-------------------------------------------------------
            /// Sets capitalisation method to be used for text input.
            ///
            /// @author Ian Copland
            ///
            /// @param The capitalisation method.
            //-------------------------------------------------------
            virtual void SetCapitalisation(Capitalisation in_capitalisation) = 0;
            //-------------------------------------------------------
            /// @author S Downie
            ///
            /// @param A delegate that is called when text buffer is
            /// changed.
            //-------------------------------------------------------
			virtual void SetTextBufferChangedDelegate(const TextBufferChangedDelegate& in_delegate) = 0;
		};
	}
}

#endif


