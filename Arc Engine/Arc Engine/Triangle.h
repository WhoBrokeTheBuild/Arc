#pragma once

#ifndef __TRIANGLE_H__
#define __TRIANGLE_H__

#include "GameObject.h"
#include "Vector2.h"
#include "MathFunc.h"

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

	Triangle( void ) { A = B = C = Vector2::ZERO; }
	Triangle( Point a, Point b, Point c);
	Triangle( float ax, float ay, float bx, float by, float cx, float cy);
	virtual ~Triangle( void ) { }

	virtual string toString( void ) const;

	bool containsPoint(Point p);
	bool containsCircle(Circle other);
	bool containsRect(Rect other);
	bool containsTriangle(Triangle other);

	bool linesIntersect( Point L1P1, Point L1P2, Point L2P1, Point L2P2);
	
};

#endif