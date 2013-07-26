#pragma once

#ifndef __BALL_H__
#define __BALL_H__

#include "Common.h"
#include <Arc/ICollidable.h>
#include <Arc/IPhysicsObject.h>
#include <Arc/IDrawable.h>

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
        _speed,
        _damping;

public:

    Ball( void );
    virtual ~Ball( void ) { term(); }

    virtual void init( Vector2 pos, float depth = 0.0f );
    virtual void term( void );

    virtual string toString( void ) const { return "Ball"; }

    virtual void update( const Event& event );
    virtual void render( const Event& event );

    virtual void render( const RenderTarget* renderTarget, const Vector2 pos );

    virtual void setTarget( Point target );

}; // class Ball

#endif // __BALL_H__