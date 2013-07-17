
#include "ArcCommon.h"
#include "RenderTarget.h"
#pragma  once

#ifndef __ICOLLIDABLE_H__
#define __ICOLLIDABLE_H__

#include "Collider.h"
#include "RectCollider.h"
#include "CircleCollider.h"

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

#endif