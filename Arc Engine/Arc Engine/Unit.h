#pragma once

namespace Arc
{

#include "Common.h"
#include "EventDispatcher.h"

class Unit :
    public EventDispatcher
{
public:

    Vector2
        Pos;

    float
        Depth;

    Unit( void ) { }
    virtual ~Unit( void ) { term(); }

    virtual void init( Vector2 pos, float depth = 0.0f ) { Pos = pos; Depth = depth; }
    virtual void term( void ) { }

    virtual void update( const Event& event ) { }
    virtual void render( const Event& event ) { }

};

}
