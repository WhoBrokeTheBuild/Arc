#pragma once

#ifndef __ARC_ICOLLIDABLE_H__
#define __ARC_ICOLLIDABLE_H__

#include "Common.h"
#include "Collider.h"
#include "RectCollider.h"
#include "CircleCollider.h"

namespace Arc
{
    class ICollidable
    {
    protected:

        Collider
            *_pCollider;

    public:

        ~ICollidable( void ) { term(); }

        virtual void init( RectCollider Collider )
        {
            _pCollider = new RectCollider(Collider.RectMask);
        }

        virtual void init( CircleCollider Collider )
        {
            _pCollider = new CircleCollider(Collider.CircleMask);
        }

        virtual void term( void )
        {
            delete _pCollider;
        }

        virtual void collided( void ) { }

    };
}

#endif
