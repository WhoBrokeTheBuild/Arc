#pragma once

#ifndef __GAME_H__
#define __GAME_H__

#include "ArcCommon.h"
#include "EventDispatcher.h"
#include "Event.h"

#include "GraphicsSystem.h"
#include "RenderTarget.h"

#include "Animation.h"
#include "Sprite.h"
#include "Texture.h"

#include "CachedText.h"

#include "InputSystem.h"

#include "Timer.h"

#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_opengl.h>

class Game :
    public EventDispatcher
{
protected:

    GraphicsSystem
        *_pGraphicsSystem;

    InputSystem 
        *_pInputSystem;

    bool
        _running;

    float 
        _targetFPS,
        _currentFPS;

public:

    static const EventType 
        EVENT_ENTER_FRAME,
        EVENT_FRAME,
        EVENT_EXIT_FRAME,
        EVENT_RENDER_START,
        EVENT_RENDER,
        EVENT_RENDER_END,
        EVENT_GAME_START,
        EVENT_GAME_END;

    Game( void );
    virtual ~Game( void );

    virtual string toString( void ) const;

    virtual void init( void );
    virtual void term( void );

    void start( void );
    void stop ( const Event& event );

    void updateFrame( const FrameData&  frameData );
    void renderFrame( const RenderData& renderData );

    virtual void update( const Event& event );
    virtual void render( const Event& event );
};

#endif
