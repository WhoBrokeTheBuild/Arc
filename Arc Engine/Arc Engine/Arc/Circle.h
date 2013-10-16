#pragma once

#ifndef __ARC_CIRCLE_H__
#define __ARC_CIRCLE_H__

#include "ManagedObject.h"
#include "ISerializable.h"
#include "Functions.h"

#include "Vector2.h"

namespace Arc
{
    class Rect;

	/** A circle storing a Position and a Radius that is centered at its position
	 */
    class Circle :
        public ManagedObject,
        public ISerializable
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

		// Initialize an empty circle
		inline Circle( void )
			: X(0.0f),
			  Y(0.0f), 
			  Radius(0.0f)
		{ }

		// Initialize a circle with a x, y, and radius
		inline Circle( float x, float y, float radius ) 
			: X(x),
			  Y(y),
			  Radius(radius) 
		{ }

		// Initialize a circle with a position and a radius
		inline Circle( Point pos, float radius ) 
			: X(pos.X),
			  Y(pos.Y), 
			  Radius(radius) 
		{ }

        virtual inline ~Circle( void ) { }

        virtual inline string toString( void ) const
        {
            stringstream ss;
            ss << "Circle [X: " << X << ", Y: " << Y << ", R:" << Radius << "]";
            return ss.str();
        }

        virtual int serialize( ostream &stream );
        virtual int deserialize( istream &stream );

        inline Point getPos( void ) const { return Point(X, Y); }

        inline float getDiameter( void ) const { return Radius * 2.0f; }
		inline void  setDiameter( float diameter ) { Radius = diameter * 0.5f; }

		// Get the top Y location of the circle
		inline float getTop   ( void ){ return Y - Radius; }
		// Get the bottom Y location of the circle
		inline float getBottom( void ){ return Y + Radius; }
		// Get the left X location of the circle
		inline float getLeft  ( void ){ return X - Radius; }
		// Get the right X location of the circle
        inline float getRight ( void ){ return X + Radius; }

		// Get the bounding rectangle around the circle
        virtual inline Rect getBounds( void ) { return Rect(getLeft(), getTop(), getDiameter(), getDiameter()); }

        virtual inline bool intersectsCircle(Circle other) { return (getPos().getDistanceTo(point) < Radius); }
        virtual bool        intersectsRect  (Rect   other);

        virtual bool containsPoint(Point  point);

    }; // class Circle

    struct CompCircle
        : public std::binary_function<Circle, Circle, bool>
    {
        inline bool operator()(const Circle& lhs, const Circle& rhs) const
        {
            return lhs.X < rhs.X; // Simple Sorting
        }
    }; // struct CompRect

} // namespace Arc

#endif // __ARC_CIRCLE_H__
