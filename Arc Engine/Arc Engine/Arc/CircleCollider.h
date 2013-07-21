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

        virtual bool check( Vector2 pos, Collider* pOther );

        virtual string toString( void ) const { return "Circle Collider"; }

    }; // class CircleCollider

} // namespace Arc

#endif // __ARC_CIRCLE_COLLIDER_H__
