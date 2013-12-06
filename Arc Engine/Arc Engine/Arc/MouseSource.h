#pragma once

#ifndef __ARC_MOUSE_SOURCE_H__
#define __ARC_MOUSE_SOURCE_H__

#include "Common.h"
#include "EventDispatcher.h"

#include "Mouse.h"
#include "InputState.h"
#include "Map.h"

namespace Arc
{
	class InputSystem;
	
	/** Class for managing mouse input and dispatching events
	  */
    class MouseSource :
        public EventDispatcher
	{

		friend class InputSystem;

    private:

		InputSystem* _pInputSystem;

		// SDL managed array of the mouse button states
        uint8_t _sdlButtonStates;

    protected:

		// Map of mouse buttons to their states (up, down, pressed, released)
        Map<MouseButton, InputState> _buttonStates;

		// Current mouse position
        Point _mousePos;

		// Change in the mouse position between the current frame and the last
        Vector2 _mouseDelta;
		
		/* Handles a single SDL_Event for reading input only available through SDL Events
		 * 
		 * @param sdlEvent: The SDL Event to handle
		 */
		virtual void handleSDLEvent( SDL_Event sdlEvent );

    public:

        static const EventType EVENT_MOUSE_MOVED;
        static const EventType EVENT_MOUSE_PRESSED;
        static const EventType EVENT_MOUSE_RELEASED;
		static const EventType EVENT_MOUSE_HELD;
		static const EventType EVENT_MOUSE_WHEEL_UP;
		static const EventType EVENT_MOUSE_WHEEL_DOWN;
		
		/* Creates a mouse source
		 */
        MouseSource( InputSystem* pInputSystem );

        virtual ~MouseSource( void );

        virtual inline string toString( void ) const { return "Mouse Source"; }
		
		/* Handler for the update event. Polls SDL for the current mouse state, then iterates 
		 * over the _buttonStates map comparing the current states to the previous states 
		 * and updating them. After each button is processed the events are fired. Events are 
		 * fired for the current mouse position if the mouse has moved
		 *
		 * @param event: The event holding the frame data
		 */
        virtual void eventUpdate( const Event& event );

    }; // class MouseSource

} // namespace Arc

#endif // __MOUSE_SOURCE_H__
