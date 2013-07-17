#pragma once

#ifndef __COLLIDER_H__
#define __COLLIDER_H__

#include "ArcCommon.h"

class Collider
{
public:

    virtual bool check( Vector2 pos, Collider* pOther ) = 0;

};

#endif