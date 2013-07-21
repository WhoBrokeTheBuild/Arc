#pragma once

#ifndef __ARC_UNIT_H__
#define __ARC_UNIT_H__

#include "Common.h"
#include "EventDispatcher.h"

namespace Arc
{
    class Unit :
        public EventDispatcher
    {
    public:

        Point
            Pos;

        float
            Depth;

        Unit( void ) 
        {
            Pos   = Point::ZERO;
            Depth = 0.0f;
        }

        virtual ~Unit( void ) { term(); }

        virtual void init( Vector2 pos, float depth = 0.0f )
        {
            Pos = pos;
            Depth = depth;
        }

        virtual void term( void ) { }

        virtual void update( const Event& event ) { }
        virtual void render( const Event& event ) { }

    }; // class Unit

} // namespace Arc

#endif // __ARC_UNIT_H__