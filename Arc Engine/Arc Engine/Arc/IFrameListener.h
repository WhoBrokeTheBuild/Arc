#pragma once

#ifndef __ARC_IFRAME_LISTENER_H__
#define __ARC_IFRAME_LISTENER_H__

#include "Common.h"
#include "EventDispatcher.h"

#include "Program.h"

namespace Arc
{
    class IFrameListener
    {
    public:

        IFrameListener( void ) { }
        virtual ~IFrameListener( void ) { term(); };

        virtual void init( void )
        {
            gpEventDispatcher->addEventListener(Program::EVENT_UPDATE, this, &IFrameListener::update);
            gpEventDispatcher->addEventListener(Program::EVENT_RENDER, this, &IFrameListener::render);
        }

        virtual void term( void )
        {
            gpEventDispatcher->removeEventListener(Program::EVENT_RENDER, this, &IFrameListener::render);
            gpEventDispatcher->removeEventListener(Program::EVENT_UPDATE, this, &IFrameListener::update);
        }

        virtual void update( const Event& event ) { };
        virtual void render( const Event& event ) { };

    }; // class IFrameListener
    
} // namespace Arc

#endif // __ARC_IFRAME_LISTENER_H__
