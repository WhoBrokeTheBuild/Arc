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
    class KeyboardSource :
        public EventDispatcher
    {
    private:

        uint8_t
            *_sdlKeys;

    protected:

        Map<KeyboardKey, InputState>
            _keyStates;

    public:

        static const EventType
            EVENT_KEY_PRESSED,
            EVENT_KEY_RELEASED,
            EVENT_KEY_HELD;

        KeyboardSource( void );
        virtual ~KeyboardSource( void ) { term(); }

        virtual inline string toString( void ) const { return "Keyboard Source"; }

        virtual void init( void );
        virtual void term( void );

        virtual void update( const Event& event );

    }; // class KeyboardSource

} // namespace Arc

#endif // __ARC_KEYBOARD_SOURCE_H__
