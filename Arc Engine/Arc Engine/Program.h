#pragma once

#ifndef __ARC_PROGRAM_H__
#define __ARC_PROGRAM_H__

#include "Common.h"
#include "EventDispatcher.h"
#include "Event.h"

#include "GraphicsSystem.h"
#include "RenderTarget.h"

#include "Animation.h"
#include "Sprite.h"
#include "Texture.h"

#include "CachedText.h"

#include "InputSystem.h"

#include "AudioSystem.h"

#include "Timer.h"

#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_opengl.h>

namespace Arc
{
    class Program :
        public EventDispatcher
    {
    protected:

        GraphicsSystem
            *_pGraphicsSystem;

        InputSystem
            *_pInputSystem;

        AudioSystem
            *_pAudioSystem;

        bool
            _running;

        float
            _targetFPS,
            _currentFPS;

    public:

        static const EventType
            EVENT_UPDATE_START,
            EVENT_UPDATE,
            EVENT_UPDATE_END,
            EVENT_RENDER_START,
            EVENT_RENDER,
            EVENT_RENDER_END,
            EVENT_EXIT;

        Program( void ) { }
        virtual ~Program( void ) { term(); }

        virtual string toString( void ) const;

        virtual void init( Size windowSize = Size(640, 480), string windowTitle = "Arc" );
        virtual void term( void );

        virtual void start( void );
        virtual void stop ( const Event& event );

        virtual void updateFrame( const FrameData&  frameData );
        virtual void renderFrame( const RenderData& renderData );

        virtual void initCore( void );
        virtual void initGraphics( Size windowSize, string windowTitle );
        virtual void initAudio   ( void );
        virtual void initInput   ( void );

        virtual void update( const Event& event ) { };
        virtual void render( const Event& event ) { };
    };
}

#endif