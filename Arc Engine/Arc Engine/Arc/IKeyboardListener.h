#pragma once

#ifndef __ARC_IKEYBOARD_LISTENER_H__
#define __ARC_IKEYBOARD_LISTENER_H__

#include "Common.h"
#include "KeyboardSource.h"
#include "GraphicalProgram.h"

namespace Arc
{
	/** Interface for listening to keyboard events
	  */
    class IKeyboardListener
    {
    public:

        inline IKeyboardListener( void )
		{
			InputSystem* pSys = GraphicalProgram::getInputSystem();

			if (pSys != nullptr)
			{
				GraphicalProgram::getInputSystem()->addEventListener(KeyboardSource::EVENT_KEY_PRESSED,  this, &IKeyboardListener::keyPressed);
				GraphicalProgram::getInputSystem()->addEventListener(KeyboardSource::EVENT_KEY_RELEASED, this, &IKeyboardListener::keyReleased);
				GraphicalProgram::getInputSystem()->addEventListener(KeyboardSource::EVENT_KEY_HELD,     this, &IKeyboardListener::keyHeld);
			}
        }

        virtual inline ~IKeyboardListener( void )
		{
			InputSystem* pSys = GraphicalProgram::getInputSystem();

			if (pSys != nullptr)
			{
				GraphicalProgram::getInputSystem()->removeEventListener(KeyboardSource::EVENT_KEY_HELD,     this, &IKeyboardListener::keyHeld);
				GraphicalProgram::getInputSystem()->removeEventListener(KeyboardSource::EVENT_KEY_RELEASED, this, &IKeyboardListener::keyReleased);
				GraphicalProgram::getInputSystem()->removeEventListener(KeyboardSource::EVENT_KEY_PRESSED,  this, &IKeyboardListener::keyPressed);
			}
        }

        virtual inline void keyPressed ( const Event& event ) { };
        virtual inline void keyReleased( const Event& event ) { };
        virtual inline void keyHeld    ( const Event& event ) { };

    }; // class IKeyboardListener

} // namespace Arc

#endif
