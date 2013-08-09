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

    virtual inline string toString( void ) const { return "Wall"; }

    virtual void update( const FrameData* event  );
    virtual void render( const RenderData* event );

}; // class Wall

#endif // __WALL_H__