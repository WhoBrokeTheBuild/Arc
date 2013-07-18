#pragma once

#ifndef __IPHYSICS_OBJECT_H__
#define __IPHYSICS_OBJECT_H__

#include "ArcCommon.h"
#include "RenderTarget.h"

class IPhysicsObject
{
public:

    Vector2
        Acc,
        Vel;

    virtual void init( Vector2 vel = Vector2::ZERO, Vector2 acc = Vector2::ZERO )
    {
        Vel = vel;
        Acc = acc;
    }

    virtual void update( Vector2& pos, double delta )
    {
        pos += Vel;
        Vel += Acc;
    }

};

#endif
