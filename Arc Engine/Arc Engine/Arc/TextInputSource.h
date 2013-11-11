#pragma once

#ifndef __ARC_TEXT_INPUT_SOURCE_H__
#define __ARC_TEXT_INPUT_SOURCE_H__

#include "Common.h"
#include "EventDispatcher.h"
#include "IKeyboardListener.h"

#include "ArrayList.h"
#include "Queue.h"

namespace Arc
{
	/** Event Data for a text input event
	  */
    class TextInputData
        : public EventData
    {
    public:

		// The character that was entered
        char
            Char;

		// The direction for the arrow keys, page up/page down, and home/end
        Direction
            Dir;

        TextInputData( Direction dir )
            : Char('\0'),
              Dir(dir)
        {
        }

        TextInputData( char ch = '\0', Direction dir = INVALID_DIRECTION )
            : Char(ch),
              Dir(dir)
        {
        }

        virtual ~TextInputData( void ) { }

        virtual inline string toString( void ) const { return "Text Input Data"; }

        virtual EventData* clone( void ) const { return New TextInputData(Char, Dir); }

    }; // class TextInputData
	
	/** Class for managing text input and dispatching events
	  */
    class TextInputSource :
        public EventDispatcher,
        public IKeyboardListener
    {
    protected:

        bool
            _shiftDown,    // Whether the shift key is down or not
            _capsLockDown; // Whether the caps lock key is down or not

		// Array of keyboard keys that are valid text inputs
        ArrayList<KeyboardKey>
            _validInputs;

    public:

        static const EventType
            EVENT_TEXT_INPUT_CHAR,
            EVENT_TEXT_INPUT_NEWLINE,
            EVENT_TEXT_INPUT_BACKSPACE,
            EVENT_TEXT_INPUT_DELETE,
            EVENT_TEXT_INPUT_TAB,
            EVENT_TEXT_INPUT_ARROWS,
            EVENT_TEXT_INPUT_HOME_END;

		// TODO: Add Page Up/Page Down
        // TODO: Add Insert Mode

        TextInputSource(void);
        virtual ~TextInputSource(void);

        virtual inline string toString( void ) const { return "Text Input Source"; }

        virtual void update( const Event& event );

        virtual void keyPressed ( const Event& event );
        virtual void keyReleased( const Event& event );
        virtual void keyHeld    ( const Event& event );

    }; // class TextInputSource

} // namespace Arc

#endif // __ARC_TEXT_INPUT_SOURCE_H__
