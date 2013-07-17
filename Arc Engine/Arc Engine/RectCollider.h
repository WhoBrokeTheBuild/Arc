#pragma once

#ifndef __RECT_COLLIDER_H__
#define __RECT_COLLIDER_H__

#include "ArcCommon.h"
#include "Collider.h"

class CircleCollider;

class RectCollider
    : public Collider
{
public:

    Rect
        RectMask;

    RectCollider( Rect mask ) { RectMask = mask; }
    RectCollider( Vector2 pos, Size size) { RectMask = Rect(pos, size); }
    RectCollider( float x, float y, float width, float height) { RectMask = Rect(x, y, width, height); }

    virtual bool check( Vector2 pos, Collider* pOther );

};

#endif