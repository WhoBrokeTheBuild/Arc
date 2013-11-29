#pragma once

#ifndef __ARC_IFRAME_LISTENER_H__
#define __ARC_IFRAME_LISTENER_H__

#include "Common.h"
#include "EventDispatcher.h"

#include "GraphicalProgram.h"

namespace Arc
{
	/** An interface for listening to update and render events
	  *
	  * @interface
	  */
    class IFrameListener
    {
    public:

        inline IFrameListener( void ) 
		{
            GraphicalProgram::getInstance()->addEventListener(GraphicalProgram::EVENT_UPDATE, this, &IFrameListener::update);
            GraphicalProgram::getInstance()->addEventListener(GraphicalProgram::EVENT_RENDER, this, &IFrameListener::render);
		}

        virtual inline ~IFrameListener( void ) 
		{
            GraphicalProgram::getInstance()->removeEventListener(GraphicalProgram::EVENT_RENDER, this, &IFrameListener::render);
            GraphicalProgram::getInstance()->removeEventListener(GraphicalProgram::EVENT_UPDATE, this, &IFrameListener::update);
		};

        virtual inline void update( const Event& event ) { };
        virtual inline void render( const Event& event ) { };

    }; // class IFrameListener
    
} // namespace Arc

#endif // __ARC_IFRAME_LISTENER_H__
