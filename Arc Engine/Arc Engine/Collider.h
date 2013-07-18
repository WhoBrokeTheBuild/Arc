#pragma once

namespace Arc
{

#ifndef __ARC_COLLIDER_H__
#define __ARC_COLLIDER_H__

#include "Common.h"

class Collider
{
public:

    virtual ~Collider( void ) { }

    virtual bool check( Vector2 pos, Collider* pOther ) = 0;

};

#endif

}
