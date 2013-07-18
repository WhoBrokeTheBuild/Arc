#include "Triangle.h"
#include "Circle.h"
#include "Rect.h"

Triangle Triangle::ZERO = Triangle (Point::ZERO, Point::ZERO, Point::ZERO);
Triangle Triangle::RIGHT = Triangle(Point(0,0), Point(0,1),  Point(1,1));

Triangle::Triangle( Point a, Point b, Point c )
{
	A = a;
	B = b;
	C = c;

	if( B.Y < A.Y)
	{
		Vector2 tmpA = A;
		A = B;
		B = tmpA;
	}
	if(C.Y < A.Y)
	{
		Vector2 tmpA = A;
		A = C;
		C = tmpA;
	}
	if(C.X < B.X)
	{
		Vector2 tmpB = B;
		B = C;
		C = tmpB;
	}
}

Triangle::Triangle( float ax, float ay, float bx, float by, float cx, float cy )
{
	A = Point(ax, ay);
	B = Point(bx, by);
	C = Point(cx, cy);

	if( B.Y < A.Y)
	{
		Vector2 tmpA = A;
		A = B;
		B = tmpA;
	}
	if(C.Y < A.Y)
	{
		Vector2 tmpA = A;
		A = C;
		C = tmpA;
	}
	if(C.X < B.X)
	{
		Vector2 tmpB = B;
		B = C;
		C = tmpB;
	}
}

std::string Triangle::toString( void ) const
{
	stringstream ss;
	ss << "Triangle [A: " << A << ", B: " << B << ", C: " << C << "]";
	return ss.str();
}

bool Triangle::containsPoint( Point p )
{
	// Compute vectors
	Vector2 
		v0 = C - A,
		v1 = B - A,
		v2 = p - A;

	// Compute dot products
	float 
		dot00 = v0.dot(v0),
		dot01 = v0.dot(v1),
		dot02 = v0.dot(v2),
		dot11 = v1.dot(v1),
		dot12 = v2.dot(v2);

	// Compute barycentric coordinates
	float invDenom = 1 / (dot00 * dot11 - dot01 * dot01);
	float u = (dot11 * dot02 - dot01 * dot12) * invDenom;
	float v = (dot00 * dot12 - dot01 * dot02) * invDenom;

	return (u >= 0) && (v >= 0) && (u + v < 1);
}

bool Triangle::containsCircle( Circle other )
{
	if(other.containsPoint(A) || other.containsPoint(B) || other.containsPoint(C))
		return true;

	if(containsPoint(other.pos()))
		return true;

	Vector2
		e1 = B - A,
		e2 = C - B,
		e3 = A - C,
		c1 = other.pos() - A,
		c2 = other.pos() - B,
		c3 = other.pos() - C;

	
	float 
		k,
		len;

	// Edge 1;
	k = c1.dot(e1);

	if( k > 0 )
	{
		len = e1.dot(e1);

		if( k < len )
			if(c1.dot(c1) * len <= k*k)
				return true;
	}

	// Edge 2
	k = c2.dot(e2);
	
	if( k > 0)
	{
		len = e2.dot(e2);

		if( k < len)
			if(c2.dot(c2) * len <= k*k)
				return true;
	}

	// Edge 3
	k = c3.dot(e3);
	
	if( k > 0)
	{
		len = e3.dot(e3);

		if( k < len)
			if(c3.dot(c3) * len <= k*k)
				return true;
	}

	return false;
}

bool Triangle::containsRect(Rect other)
{
	if(other.containsPoint(A) || other.containsPoint(B) || other.containsPoint(C))
		return true;

	if(containsPoint(other.center()))
		return true;

	Point
		oTopLeft = Point(other.left(), other.top()),
		oTopRight = Point(other.right(), other.top()),
		oBotLeft = Point(other.left(), other.bottom()),
		oBotRight = Point(other.right(), other.bottom());

	if( containsPoint(oTopLeft) || 
		containsPoint(oTopRight) || 
		containsPoint(oBotLeft) ||		
		containsPoint(oBotRight) )
		return true;

	if( linesIntersect(A, B, oTopLeft, oTopRight) ||
		linesIntersect(A, B, oTopLeft, oBotLeft) ||
		linesIntersect(A, B, oTopRight, oBotRight) ||
		linesIntersect(A, B, oBotLeft, oBotRight) ||
		linesIntersect(C, B, oTopLeft, oTopRight) ||
		linesIntersect(C, B, oTopLeft, oBotLeft) ||
		linesIntersect(C, B, oTopRight, oBotRight) ||
		linesIntersect(C, B, oBotLeft, oBotRight) ||
		linesIntersect(A, C, oTopLeft, oTopRight) ||
		linesIntersect(A, C, oTopLeft, oBotLeft) ||
		linesIntersect(A, C, oTopRight, oBotRight) ||
		linesIntersect(A, C, oBotLeft, oBotRight) )
		return true;

	return false;
}

bool Triangle::containsTriangle(Triangle other)
{
	if(other.containsPoint(A) || other.containsPoint(B) || other.containsPoint(C))
		return true;

	if(containsPoint(other.A) || containsPoint(other.B) || containsPoint(other.C))
		return true;

	if( linesIntersect(A, B, other.A, other.B) ||
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

bool Triangle::linesIntersect( Point L1P1, Point L1P2, Point L2P1, Point L2P2)
{
	float 
		ua = 0,
		ub = 0,
		ud = (L2P2.Y - L2P1.Y) * (L1P2.X - L1P1.X) - (L2P2.X - L2P1.X) * (L1P2.Y - L1P1.Y);

	if( ud != 0 )
	{
		ua = ((L2P2.X - L2P1.X) * (L1P1.Y - L2P1.Y) - (L2P2.Y - L2P1.Y) * (L1P1.X - L2P1.X)) / ud;
		ub = ((L1P2.X - L1P1.X) * (L1P1.Y - L2P1.Y) - (L1P2.Y - L1P1.Y) * (L1P1.X - L2P1.X)) / ud;

		if(ua < 0 || ua > 1 || ub < 0 || ub > 1)
			ua = 0;
	}

	return ua != 0;
}