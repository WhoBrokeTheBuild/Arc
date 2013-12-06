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
				GraphicalProgram::getInputSystem()->addEventListener(KeyboardSource::EVENT_KEY_PRESSED,  this, &IKeyboardListener::eventKeyPressed);
				GraphicalProgram::getInputSystem()->addEventListener(KeyboardSource::EVENT_KEY_RELEASED, this, &IKeyboardListener::eventKeyReleased);
				GraphicalProgram::getInputSystem()->addEventListener(KeyboardSource::EVENT_KEY_HELD,     this, &IKeyboardListener::eventKeyHeld);
			}
        }

        virtual inline ~IKeyboardListener( void )
		{
			InputSystem* pSys = GraphicalProgram::getInputSystem();

			if (pSys != nullptr)
			{
				GraphicalProgram::getInputSystem()->removeEventListener(KeyboardSource::EVENT_KEY_HELD,     this, &IKeyboardListener::eventKeyHeld);
				GraphicalProgram::getInputSystem()->removeEventListener(KeyboardSource::EVENT_KEY_RELEASED, this, &IKeyboardListener::eventKeyReleased);
				GraphicalProgram::getInputSystem()->removeEventListener(KeyboardSource::EVENT_KEY_PRESSED,  this, &IKeyboardListener::eventKeyPressed);
			}
        }

        virtual inline void eventKeyPressed( const Event& event ) { };

        virtual inline void eventKeyReleased( const Event& event ) { };

        virtual inline void eventKeyHeld( const Event& event ) { };

    }; // class IKeyboardListener

} // namespace Arc

#endif
