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

        inline IFrameListener( void ) { }
        virtual inline ~IFrameListener( void ) { term(); };

        virtual inline void init( void )
        {
            gpEventDispatcher->addEventListener(Program::EVENT_UPDATE, this, &IFrameListener::update);
            gpEventDispatcher->addEventListener(Program::EVENT_RENDER, this, &IFrameListener::render);
        }

        virtual inline void term( void )
        {
            gpEventDispatcher->removeEventListener(Program::EVENT_RENDER, this, &IFrameListener::render);
            gpEventDispatcher->removeEventListener(Program::EVENT_UPDATE, this, &IFrameListener::update);
        }

        virtual inline void update( const Event& event ) { };
        virtual inline void render( const Event& event ) { };

    }; // class IFrameListener
    
} // namespace Arc

#endif // __ARC_IFRAME_LISTENER_H__
