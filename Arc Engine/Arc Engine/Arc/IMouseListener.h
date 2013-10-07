#pragma once

#ifndef __ARC_IMOUSE_LISTENER_H__
#define __ARC_IMOUSE_LISTENER_H__

#include "Common.h"
#include "MouseSource.h"

namespace Arc
{
	/** Interface for listening to mouse events
	  */
    class IMouseListener
    {
    public:

        inline IMouseListener( void )
		{
            gpEventDispatcher->addEventListener(MouseSource::EVENT_MOUSE_PRESSED,  this, &IMouseListener::mousePressed);
            gpEventDispatcher->addEventListener(MouseSource::EVENT_MOUSE_RELEASED, this, &IMouseListener::mouseReleased);
            gpEventDispatcher->addEventListener(MouseSource::EVENT_MOUSE_HELD,     this, &IMouseListener::mouseHeld);
            gpEventDispatcher->addEventListener(MouseSource::EVENT_MOUSE_MOVED,    this, &IMouseListener::mouseMoved);
		}

        virtual inline ~IMouseListener( void )
		{
            gpEventDispatcher->removeEventListener(MouseSource::EVENT_MOUSE_MOVED,    this, &IMouseListener::mouseMoved);
            gpEventDispatcher->removeEventListener(MouseSource::EVENT_MOUSE_HELD,     this, &IMouseListener::mouseHeld);
            gpEventDispatcher->removeEventListener(MouseSource::EVENT_MOUSE_RELEASED, this, &IMouseListener::mouseReleased);
            gpEventDispatcher->removeEventListener(MouseSource::EVENT_MOUSE_PRESSED,  this, &IMouseListener::mousePressed);
		}

        virtual inline void mousePressed ( const Event& event ) { };
        virtual inline void mouseReleased( const Event& event ) { };
        virtual inline void mouseHeld    ( const Event& event ) { };
        virtual inline void mouseMoved   ( const Event& event ) { };

    }; // class IMouseListener

} // namespace Arc

#endif
