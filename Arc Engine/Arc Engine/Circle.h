#pragma once

#ifndef __ARC_CIRCLE_H__
#define __ARC_CIRCLE_H__

#include "GameObject.h"
#include "Vector2.h"

class Rect;

class Circle :
    public GameObject
{
private:

public:

    static Circle
        ZERO,
        ONE;

    float
        X,
        Y,
        Radius;

    Circle( void ) { X = Y = Radius = 0; }
    Circle( float x, float y, float radius );
    Circle( Vector2 pos, float radius );
    virtual ~Circle( void ) { }

    virtual string toString( void ) const;

    inline Vector2 pos ( void ) { return Vector2(X, Y); }

    inline float diameter( void ) { return Radius * 2.0f; }

    inline float top   ( void ){ return Y - Radius; }
    inline float bottom( void ){ return Y + Radius; }
    inline float left  ( void ){ return X - Radius; }
    inline float right ( void ){ return X + Radius; }

    bool containsCircle(Circle other);
    bool containsRect  (Rect other);
    bool containsPoint (Vector2 point);

};

#endif
