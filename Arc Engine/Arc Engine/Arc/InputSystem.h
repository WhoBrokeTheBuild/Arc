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

        KeyboardSource
            *_pKeyboardSource;

        MouseSource
            *_pMouseSource;

        TextInputSource
            *_pTextInputSource;

        virtual void handleSDLEvent( SDL_Event sdlEvent );

    public:

        InputSystem( void );
        virtual ~InputSystem( void ) { term(); }

        virtual string toString( void ) const;

        virtual void init( void );
        virtual void term( void );

        virtual void update( const Event& event );

    }; // class InputSystem

} // namespace Arc

#endif // __ARC_INPUT_SYSTEM_H__
