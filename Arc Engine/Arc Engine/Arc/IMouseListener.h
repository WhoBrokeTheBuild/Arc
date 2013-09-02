#pragma once

#ifndef __ARC_IMOUSE_LISTENER_H__
#define __ARC_IMOUSE_LISTENER_H__

#include "Common.h"
#include "MouseSource.h"

namespace Arc
{
    class IMouseListener
    {
    public:

        inline IMouseListener( void ) { }
        virtual inline ~IMouseListener( void ) { term(); };

        inline virtual void init( void )
        {
            gpEventDispatcher->addEventListener(MouseSource::EVENT_MOUSE_PRESSED,  this, &IMouseListener::mousePressed);
            gpEventDispatcher->addEventListener(MouseSource::EVENT_MOUSE_RELEASED, this, &IMouseListener::mouseReleased);
            gpEventDispatcher->addEventListener(MouseSource::EVENT_MOUSE_HELD,     this, &IMouseListener::mouseHeld);
            gpEventDispatcher->addEventListener(MouseSource::EVENT_MOUSE_MOVED,    this, &IMouseListener::mouseMoved);
        }

        inline virtual void term( void )
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

    };
}

#endif
