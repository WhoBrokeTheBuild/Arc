#pragma once

#ifndef __WALL_H__
#define __WALL_H__

#include "Common.h"
#include <Arc/Unit.h>
#include <Arc/ICollidable.h>
#include <Arc/IDrawable.h>

class Wall :
    public Unit,
    public ICollidable,
    public IDrawable
{
private:

    Rect
        _area;

public:

    Wall( void );
    virtual ~Wall( void ) { term(); }

    virtual void init( Vector2 pos, Rect area, float depth = 0.0f );
    virtual void term( void );

    virtual string toString( void ) const { return "Wall"; }

    virtual void update( const Event& event );
    virtual void render( const Event& event );

    virtual void render( const RenderTarget* renderTarget, const Vector2 pos );

}; // class Wall

#endif // __WALL_H__