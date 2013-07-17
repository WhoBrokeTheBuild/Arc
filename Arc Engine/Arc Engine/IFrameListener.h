#pragma once

#ifndef __IFRAME_LISTENER_H__
#define __IFRAME_LISTENER_H__

#include "ArcCommon.h"
#include "EventDispatcher.h"
#include "ArcApp.h"

class IFrameListener
{
public:

    IFrameListener( void ) { }
    virtual ~IFrameListener( void ) { term(); };

    virtual void init( void )
    {
        gpEventDispatcher->addEventListener(ArcApp::EVENT_UPDATE, this, &IFrameListener::update);
        gpEventDispatcher->addEventListener(ArcApp::EVENT_RENDER, this, &IFrameListener::render);
    }

    virtual void term( void )
    {
        gpEventDispatcher->removeEventListener(ArcApp::EVENT_RENDER, this, &IFrameListener::render);
        gpEventDispatcher->removeEventListener(ArcApp::EVENT_UPDATE, this, &IFrameListener::update);
    }

    virtual void update( const Event& event ) { };
    virtual void render( const Event& event ) { };

};

#endif