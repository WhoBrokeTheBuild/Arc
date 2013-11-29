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
            GraphicalProgram::getInstance()->addEventListener(GraphicalProgram::EVENT_UPDATE, this, &IFrameListener::eventUpdate);
            GraphicalProgram::getInstance()->addEventListener(GraphicalProgram::EVENT_RENDER, this, &IFrameListener::eventRender);
		}

        virtual inline ~IFrameListener( void ) 
		{
            GraphicalProgram::getInstance()->removeEventListener(GraphicalProgram::EVENT_RENDER, this, &IFrameListener::eventRender);
            GraphicalProgram::getInstance()->removeEventListener(GraphicalProgram::EVENT_UPDATE, this, &IFrameListener::eventUpdate);
		};

        virtual inline void eventUpdate( const Event& event ) { };
        virtual inline void eventRender( const Event& event ) { };

    }; // class IFrameListener
    
} // namespace Arc

#endif // __ARC_IFRAME_LISTENER_H__
