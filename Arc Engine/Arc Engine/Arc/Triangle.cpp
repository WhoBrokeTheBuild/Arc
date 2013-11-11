#include "Triangle.h"
#include "Circle.h"
#include "Rect.h"

Arc::Triangle Arc::Triangle::ZERO = Triangle (Point::ZERO, Point::ZERO, Point::ZERO);
Arc::Triangle Arc::Triangle::RIGHT = Triangle(Point(0, 0), Point(0, 1),  Point(1, 0));

Arc::Triangle::Triangle( Point a, Point b, Point c )
{
	A = a;
	B = b;
	C = c;

    if (B.Y < A.Y)
    {
        std::swap(A, B);
    }

    if (C.Y < A.Y)
    {
        std::swap(A, C);
    }

    if (C.X < B.X)
    {
        std::swap(B, C);
    }
}

Arc::Triangle::Triangle( Point center, float radius )
{
    A = center - Point(0.0f, radius);
    B = center + Point(cos(AngleHelper::toRad(120)) * radius, sin(AngleHelper::toRad(120)) * radius);
    C = center + Point(cos(AngleHelper::toRad(-120)) * radius, sin(AngleHelper::toRad(-120)) * radius);
}

Arc::Triangle::Triangle( float aX, float aY, float bX, float bY, float cX, float cY )
{
	A = Point(aX, aY);
	B = Point(bX, bY);
	C = Point(cX, cY);

	if (B.Y < A.Y)
	{
        std::swap(A, B);
	}

	if (C.Y < A.Y)
    {
        std::swap(A, C);
	}

	if (C.X < B.X)
    {
        std::swap(B, C);
	}
}

bool Arc::Triangle::containsPoint( Point other )
{
	// Compute vectors
	Vector2
		v0 = C - A,
		v1 = B - A,
		v2 = other - A;

	// Compute dot products
	float
		dot00 = v0.getDot(v0),
		dot01 = v0.getDot(v1),
		dot02 = v0.getDot(v2),
		dot11 = v1.getDot(v1),
		dot22 = v2.getDot(v2);

	// Compute barycentric coordinates
	float invDenom = 1 / (dot00 * dot11 - dot01 * dot01);
	float u = (dot11 * dot02 - dot01 * dot22) * invDenom;
	float v = (dot00 * dot22 - dot01 * dot02) * invDenom;

	return (u >= 0) && (v >= 0) && (u + v < 1);
}

bool Arc::Triangle::containsCircle( Circle other )
{
	if(other.containsPoint(A) || other.containsPoint(B) || other.containsPoint(C))
		return true;

	if(containsPoint(other.getPos()))
		return true;

	Vector2
		e1 = B - A,
		e2 = C - B,
		e3 = A - C,
		c1 = other.getPos() - A,
		c2 = other.getPos() - B,
		c3 = other.getPos() - C;


	float
		k,
		len;

	// Edge 1;
	k = c1.getDot(e1);

	if( k > 0 )
	{
		len = e1.getDot(e1);

		if( k < len )
			if(c1.getDot(c1) * len <= k*k)
				return true;
	}

	// Edge 2
	k = c2.getDot(e2);

	if( k > 0)
	{
		len = e2.getDot(e2);

		if( k < len)
			if(c2.getDot(c2) * len <= k*k)
				return true;
	}

	// Edge 3
	k = c3.getDot(e3);

	if( k > 0)
	{
		len = e3.getDot(e3);

		if( k < len)
			if(c3.getDot(c3) * len <= k*k)
				return true;
	}

	return false;
}

bool Arc::Triangle::containsRect( Rect other )
{
	if (other.containsPoint(A) || other.containsPoint(B) || other.containsPoint(C))
		return true;

	if (containsPoint(other.getCenter()))
		return true;

	Point
		oTopLeft  = other.getTopLeftPoint(),
		oTopRight = other.getTopRightPoint(),
		oBotLeft  = other.getBottomLeftPoint(),
		oBotRight = other.getBottomRightPoint();

	if (containsPoint(oTopLeft)  ||
		containsPoint(oTopRight) ||
		containsPoint(oBotLeft)  ||
		containsPoint(oBotRight) )
		return true;

	if (linesIntersect(A, B, oTopLeft, oTopRight)  ||
		linesIntersect(A, B, oTopLeft, oBotLeft)   ||
		linesIntersect(A, B, oTopRight, oBotRight) ||
		linesIntersect(A, B, oBotLeft, oBotRight)  ||
		linesIntersect(C, B, oTopLeft, oTopRight)  ||
		linesIntersect(C, B, oTopLeft, oBotLeft)   ||
		linesIntersect(C, B, oTopRight, oBotRight) ||
		linesIntersect(C, B, oBotLeft, oBotRight)  ||
		linesIntersect(A, C, oTopLeft, oTopRight)  ||
		linesIntersect(A, C, oTopLeft, oBotLeft)   ||
		linesIntersect(A, C, oTopRight, oBotRight) ||
		linesIntersect(A, C, oBotLeft, oBotRight)  )
		return true;

	return false;
}

bool Arc::Triangle::containsTriangle( Triangle other )
{
	if (other.containsPoint(A) || other.containsPoint(B) || other.containsPoint(C))
		return true;

	if (containsPoint(other.A) || containsPoint(other.B) || containsPoint(other.C))
		return true;

	if (linesIntersect(A, B, other.A, other.B) ||
		linesIntersect(A, B, other.A, other.C) ||
		linesIntersect(A, B, other.B, other.C) ||
		linesIntersect(C, B, other.A, other.B) ||
		linesIntersect(C, B, other.A, other.C) ||
		linesIntersect(C, B, other.B, other.C) ||
		linesIntersect(A, C, other.A, other.B) ||
		linesIntersect(A, C, other.A, other.C) ||
		linesIntersect(A, C, other.B, other.C) )
		return true;

	return false;
}
