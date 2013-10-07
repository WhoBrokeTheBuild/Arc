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

		// SDL managed array of the mouse button states
        uint8_t
            _sdlButtonStates;

    protected:

		// Map of mouse buttons to their states (up, down, pressed, released)
        Map<MouseButton, InputState>
            _buttonStates;

		// Current mouse position
        Point
            _mousePos;

		// Change in the mouse position between the current frame and the last
        Vector2
			_mouseDelta;

		// Function for reading input only available through SDL Events
		virtual void handleSDLEvent( SDL_Event sdlEvent );

    public:

        static const EventType
            EVENT_MOUSE_MOVED,
            EVENT_MOUSE_PRESSED,
            EVENT_MOUSE_RELEASED,
			EVENT_MOUSE_HELD,
			EVENT_MOUSE_WHEEL_UP,
			EVENT_MOUSE_WHEEL_DOWN;

        MouseSource( void );
        virtual ~MouseSource( void );

        virtual inline string toString( void ) const { return "Mouse Source"; }

        virtual void update( const Event& event );

    }; // class MouseSource

} // namespace Arc

#endif // __MOUSE_SOURCE_H__
