#pragma once

#ifndef __ARC_CIRCLE_COLLIDER_H__
#define __ARC_CIRCLE_COLLIDER_H__

#include "Common.h"
#include "Collider.h"

namespace Arc
{
    class RectCollider;

    class CircleCollider
        : public Collider
    {
    public:

        Circle
            CircleMask;

        CircleCollider( Circle mask ) { CircleMask = mask; }
        CircleCollider( Vector2 pos, float radius ) { CircleMask = Circle(pos, radius); }
        CircleCollider( float x, float y, float radius ) { CircleMask = Circle(x, y, radius); }

        virtual bool check( Point pos, Collider* pOther, Point otherPos );
        virtual Point getCollisionPoint( Point pos, Collider* pOther, Point otherPos );
        virtual Point center( void ) { return CircleMask.center(); }

        virtual string toString( void ) const { return "Circle Collider"; }

        virtual void render( const RenderTarget* renderTarget, Point pos, Vector2 origin = Vector2::ZERO );

    }; // class CircleCollider

} // namespace Arc

#endif // __ARC_CIRCLE_COLLIDER_H__
