#pragma once

#ifndef __ARC_COLLIDER_H__
#define __ARC_COLLIDER_H__

#include "Common.h"
#include "GameObject.h"

#include "RenderTarget.h"

namespace Arc
{
    class Collider
        : public GameObject
    {
    public:

        virtual ~Collider( void ) { }

        virtual bool check( Point pos, Collider* pOther, Point otherPos ) = 0;

        virtual void render( const RenderTarget* renderTarget, Point pos ) { }

    }; // class Collider

} // namespace Arc

#endif // __ARC_COLLIDER_H__
