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
				GraphicalProgram::getInputSystem()->addEventListener(MouseSource::EVENT_MOUSE_PRESSED,  this, &IMouseListener::mousePressed);
				GraphicalProgram::getInputSystem()->addEventListener(MouseSource::EVENT_MOUSE_RELEASED, this, &IMouseListener::mouseReleased);
				GraphicalProgram::getInputSystem()->addEventListener(MouseSource::EVENT_MOUSE_HELD,     this, &IMouseListener::mouseHeld);
				GraphicalProgram::getInputSystem()->addEventListener(MouseSource::EVENT_MOUSE_MOVED,    this, &IMouseListener::mouseMoved);
			}
		}

        virtual inline ~IMouseListener( void )
		{
			InputSystem* pSys = GraphicalProgram::getInputSystem();

			if (pSys != nullptr)
			{
				GraphicalProgram::getInputSystem()->removeEventListener(MouseSource::EVENT_MOUSE_MOVED,    this, &IMouseListener::mouseMoved);
				GraphicalProgram::getInputSystem()->removeEventListener(MouseSource::EVENT_MOUSE_HELD,     this, &IMouseListener::mouseHeld);
				GraphicalProgram::getInputSystem()->removeEventListener(MouseSource::EVENT_MOUSE_RELEASED, this, &IMouseListener::mouseReleased);
				GraphicalProgram::getInputSystem()->removeEventListener(MouseSource::EVENT_MOUSE_PRESSED,  this, &IMouseListener::mousePressed);
			}
		}

        virtual inline void mousePressed ( const Event& event ) { };
        virtual inline void mouseReleased( const Event& event ) { };
        virtual inline void mouseHeld    ( const Event& event ) { };
        virtual inline void mouseMoved   ( const Event& event ) { };

    }; // class IMouseListener

} // namespace Arc

#endif
