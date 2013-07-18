#pragma once

#ifndef __ARC_TEXT_INPUT_SOURCE_H__
#define __ARC_TEXT_INPUT_SOURCE_H__

#include "Common.h"
#include "EventDispatcher.h"
#include "IKeyboardListener.h"

#include "ArrayList.h"
#include <queue>

namespace Arc
{
    class TextInputData
        : public EventData
    {
    public:

        char
            Char;

        Direction
            Dir;

        TextInputData( Direction dir ) { Dir = dir; }
        TextInputData( char ch = '\0', Direction dir = INVALID_DIRECTION ) { Char = ch; Dir = dir; }
        virtual ~TextInputData( void ) { }

        virtual string toString( void ) const { return "Text Input Data"; }

        virtual EventData* clone( void ) const { return New TextInputData(Char, Dir); }

    };

    class TextInputSource :
        public EventDispatcher,
        public IKeyboardListener
    {
    protected:

        bool
            _shiftDown,
            _capsLockDown;

        ArrayList<KeyboardKey>
            _validInputs;

        queue<KeyboardKey>
            _inputQueue;

    public:

        static const EventType
            EVENT_TEXT_INPUT_CHAR,
            EVENT_TEXT_INPUT_NEWLINE,
            EVENT_TEXT_INPUT_BACKSPACE,
            EVENT_TEXT_INPUT_DELETE,
            EVENT_TEXT_INPUT_TAB,
            EVENT_TEXT_INPUT_ARROWS,
            EVENT_TEXT_INPUT_HOME_END;

        //TODO: Add Insert Mode

        TextInputSource(void) { }
        virtual ~TextInputSource(void) { term(); }

        virtual string toString( void ) const { return "Text Input Source"; }

        virtual void init( void );
        virtual void term( void );

        virtual void update( const Event& event );

        virtual void keyPressed ( const Event& event );
        virtual void keyReleased( const Event& event );
        virtual void keyHeld    ( const Event& event );

    };
}

#endif