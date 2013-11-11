#pragma once

#ifndef __ARC_INPUT_SYSTEM_H__
#define __ARC_INPUT_SYSTEM_H__

#include "Common.h"
#include "EventDispatcher.h"

#include <SDL/SDL.h>

#include "Mouse.h"
#include "Keyboard.h"
#include "GamePad.h"
#include "InputState.h"

#include "KeyboardSource.h"
#include "MouseSource.h"
#include "TextInputSource.h"

namespace Arc
{
    class InputSystem :
        public EventDispatcher
    {
    protected:

		// Manager for keyboard input
        KeyboardSource* _pKeyboardSource;

		// Manager for mouse input
        MouseSource* _pMouseSource;

		// Manager for text input
        TextInputSource* _pTextInputSource;

		// Function for handling the SDL Event loop
        virtual void handleSDLEvent( SDL_Event sdlEvent );

    public:

        InputSystem( void );
        virtual ~InputSystem( void );

        virtual inline string toString( void ) const { return "Input System"; }

        virtual void update( const Event& event );

    }; // class InputSystem

} // namespace Arc

#endif // __ARC_INPUT_SYSTEM_H__
