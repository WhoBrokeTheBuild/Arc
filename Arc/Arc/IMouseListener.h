#pragma once

#ifndef __ARC_IMOUSE_LISTENER_H__
#define __ARC_IMOUSE_LISTENER_H__

#include "Common.h"
#include "MouseSource.h"
#include "GraphicalProgram.h"

namespace Arc
{
	/** Interface for listening to mouse events
	  */
    class IMouseListener
    {
    public:

        inline IMouseListener( void )
		{
			InputSystem* pSys = GraphicalProgram::getInputSystem();
			
			if (pSys != nullptr)
			{
				GraphicalProgram::getInputSystem()->addEventListener(MouseSource::EVENT_MOUSE_PRESSED,  this, &IMouseListener::eventMousePressed);
				GraphicalProgram::getInputSystem()->addEventListener(MouseSource::EVENT_MOUSE_RELEASED, this, &IMouseListener::eventMouseReleased);
				GraphicalProgram::getInputSystem()->addEventListener(MouseSource::EVENT_MOUSE_HELD,     this, &IMouseListener::eventMouseHeld);
				GraphicalProgram::getInputSystem()->addEventListener(MouseSource::EVENT_MOUSE_MOVED,    this, &IMouseListener::eventMouseMoved);
			}
		}

        virtual inline ~IMouseListener( void )
		{
			InputSystem* pSys = GraphicalProgram::getInputSystem();

			if (pSys != nullptr)
			{
				GraphicalProgram::getInputSystem()->removeEventListener(MouseSource::EVENT_MOUSE_MOVED,    this, &IMouseListener::eventMouseMoved);
				GraphicalProgram::getInputSystem()->removeEventListener(MouseSource::EVENT_MOUSE_HELD,     this, &IMouseListener::eventMouseHeld);
				GraphicalProgram::getInputSystem()->removeEventListener(MouseSource::EVENT_MOUSE_RELEASED, this, &IMouseListener::eventMouseReleased);
				GraphicalProgram::getInputSystem()->removeEventListener(MouseSource::EVENT_MOUSE_PRESSED,  this, &IMouseListener::eventMousePressed);
			}
		}

        virtual inline void eventMousePressed( const Event& event ) { };

        virtual inline void eventMouseReleased( const Event& event ) { };

        virtual inline void eventMouseHeld( const Event& event ) { };

        virtual inline void eventMouseMoved( const Event& event ) { };

    }; // class IMouseListener

} // namespace Arc

#endif
