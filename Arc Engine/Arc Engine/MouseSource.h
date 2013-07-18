#pragma once

#ifndef __ARC_MOUSE_CONTROLLER_H__
#define __ARC_MOUSE_CONTROLLER_H__

#include "Common.h"
#include "EventDispatcher.h"

#include "Mouse.h"
#include "InputState.h"

#include "Map.h"

namespace Arc
{
    typedef Map<MouseButton,  InputState> MouseStateMap;

    class MouseSource :
        public EventDispatcher
    {
    private:

        uint8_t
            _sdlButtonStates;

    protected:

        MouseStateMap
            _buttonStates;

        Vector2
            _mousePos,
            _mouseDelta;

    public:

        static const EventType
            EVENT_MOUSE_MOVED,
            EVENT_MOUSE_PRESSED,
            EVENT_MOUSE_RELEASED,
            EVENT_MOUSE_HELD;

        MouseSource( void ) { }
        virtual ~MouseSource( void ) { term(); }

        virtual string toString( void ) const { return "Mouse Source"; }

        virtual void init( void );
        virtual void term( void );

        virtual void update( const Event& event );
    };
}

#endif
