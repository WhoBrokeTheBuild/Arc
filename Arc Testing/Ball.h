#pragma once

#ifndef __BALL_H__
#define __BALL_H__

#include "Common.h"
#include <Arc/ICollidable.h>
#include <Arc/IPhysicsObject.h>
#include <Arc/IDrawable.h>

#include <Arc/Sound.h>

class Ball :
    public Unit,
    public ICollidable,
    public IPhysicsObject,
    public IDrawable
{
private:

    float
        _radius,
        _gravity,
        _maxSpeed,
        _damping;

    Sound
        *_pPing,
        *_pPong;

    bool 
        _ping;

public:

    Ball( void );
    virtual ~Ball( void ) { term(); }

    virtual void init( Vector2 pos, float depth = 0.0f );
    virtual void term( void );

    virtual string toString( void ) const { return "Ball"; }

    virtual void update( const FrameData* event  );
    virtual void render( const RenderData* event );

    virtual void setTarget( Point target );

}; // class Ball

#endif // __BALL_H__