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

	/** A class for managing keyboard input and dispatching events
	  */
    class KeyboardSource :
        public EventDispatcher
	{

		friend class InputSystem;

    private:

		// SDL managed array of key states
        uint8_t* _sdlKeys;

    protected:

		InputSystem* _pInputSystem;

		// Map of keys to their states (up, down, pressed, released)
        Map<KeyboardKey, InputState> _keyStates;

		/* Handles a single SDL_Event for reading input only available through SDL Events
		 * 
		 * @param sdlEvent: The SDL Event to handle
		 */
		virtual void handleSDLEvent( SDL_Event sdlEvent );

    public:

        static const EventType EVENT_KEY_PRESSED;
        static const EventType EVENT_KEY_RELEASED;
        static const EventType EVENT_KEY_HELD;

		/* Creates a keyboard source
		 */
        KeyboardSource( InputSystem* pInputSystem );

        virtual ~KeyboardSource( void );

        virtual inline string toString( void ) const { return "Keyboard Source"; }

		/* Handler for the update event. Polls SDL for the current key states, then iterates
		 * over the keyStates map comparing the current states to the previous states and 
		 * updating them. After 
		 * each key is processed the events are fired
		 *
		 * @param event: The event holding the frame data
		 */
        virtual void eventUpdate( const Event& event );

    }; // class KeyboardSource

} // namespace Arc

#endif // __ARC_KEYBOARD_SOURCE_H__
