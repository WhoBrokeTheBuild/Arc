#pragma once

#ifndef __ARC_KEYBOARD_SOURCE_H__
#define __ARC_KEYBOARD_SOURCE_H__

#include "Common.h"
#include "EventDispatcher.h"

#include "Keyboard.h"
#include "InputState.h"
#include "Map.h"

namespace Arc
{
	class InputSystem;

	/** Class for managing keyboard input and dispatching events
	  */
    class KeyboardSource :
        public EventDispatcher
	{

		friend class InputSystem;

    private:

		// SDL managed array of key states
        uint8_t
            *_sdlKeys;

    protected:

		// Map of keys to their states (up, down, pressed, released)
        Map<KeyboardKey, InputState>
			_keyStates;

		// Function for reading input only available through SDL Events
		virtual void handleSDLEvent( SDL_Event sdlEvent );

    public:

        static const EventType
            EVENT_KEY_PRESSED,
            EVENT_KEY_RELEASED,
            EVENT_KEY_HELD;

        KeyboardSource( void );
        virtual ~KeyboardSource( void );

        virtual inline string toString( void ) const { return "Keyboard Source"; }

        virtual void update( const Event& event );

    }; // class KeyboardSource

} // namespace Arc

#endif // __ARC_KEYBOARD_SOURCE_H__
