#pragma once

#ifndef __ARC_COLLIDER_H__
#define __ARC_COLLIDER_H__

#include "Common.h"
#include "GameObject.h"

namespace Arc
{
    class Collider
        : public GameObject
    {
    public:

        virtual ~Collider( void ) { }

        virtual bool check( Vector2 pos, Collider* pOther ) = 0;

    }; // class Collider

} // namespace Arc

#endif // __ARC_COLLIDER_H__
