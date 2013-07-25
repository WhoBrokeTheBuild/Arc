#pragma once

#ifndef __ARC_TRIANGLE_H__
#define __ARC_TRIANGLE_H__

#include "GameObject.h"

#include "Vector2.h"
#include "MathFunc.h"

namespace Arc
{
    class Rect;
    class Circle;

    class Triangle :
        public GameObject
    {
    private:

    public:

	    static Triangle
		    ZERO,
		    RIGHT,
		    EQUILATERAL;

	    Point
		    A,
		    B,
		    C;

	    Triangle( void ) { A = B = C = Point::ZERO; }
        Triangle( Point center, float radius );
	    Triangle( Point a, Point b, Point c);
	    Triangle( float aX, float aY, float bX, float bY, float cX, float cY);
	    virtual ~Triangle( void ) { }

	    virtual string toString( void ) const;

	    bool containsPoint   ( Point    other );
	    bool containsCircle  ( Circle   other );
	    bool containsRect    ( Rect     other );
	    bool containsTriangle( Triangle other );
	
    }; // class Triangle

} // namespace Arc

#endif // __ARC_TRIANGLE_H__