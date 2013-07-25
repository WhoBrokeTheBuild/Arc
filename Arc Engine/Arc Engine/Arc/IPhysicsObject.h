#pragma once

#ifndef __ARC_IPHYSICS_OBJECT_H__
#define __ARC_IPHYSICS_OBJECT_H__

#include "Common.h"

namespace Arc
{
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

    }; // class IPhysicsObject

} // namespace Arc

#endif // __ARC_IPHYSICS_OBJECT_H__
