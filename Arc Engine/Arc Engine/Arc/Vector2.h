#pragma once

#ifndef __ARC_VECTOR_2_H__
#define __ARC_VECTOR_2_H__

#include "ManagedObject.h"
#include "ISerializable.h"
#include "Functions.h"

namespace Arc
{
    class Vector2;
    class Angle;

	// Aliases for different uses
    typedef Vector2 Point;
    typedef Vector2 Size;

	/** A two-part vector.
	  */
    class Vector2
        : public ManagedObject,
          public ISerializable
    {
    public:

		// Predefined constants
        static Vector2
            ZERO, 
            ONE,
            NEGATIVE_ONE;

        float
            X,
            Y;

		// Initialize a vector of zeros
        inline Vector2( void ) 
			: X(0.0f), 
			  Y(0.0f) 
		{ }

		// Initialize both X and Y to the same value
		inline Vector2( float both ) 
			: X(both),
			  Y(both)
		{ }

        inline Vector2( float x, float y )
			: X(x),
			  Y(y) 
		{ }

        virtual inline ~Vector2( void ) { }

        virtual inline string toString( void ) const
        {
            stringstream ss;
            ss << "Vector2 [X: " << X << ", Y: " << Y << "]";
            return ss.str();
        }

		// Generate a random Vector2 based on the min and max values
		inline static Vector2 rand( float minX, float minY, float maxX, float maxY )
		{
			return Vector2(randFloat(minX, maxX), randFloat(minY, maxY));
		}

		// Lerp between the start and end vectors by the fraction amount
		inline static Vector2 lerp( const Vector2& start, const Vector2& end, float fraction )
		{
			return Vector2(lerpNumber(start.X, end.X, fraction), lerpNumber(start.Y, end.Y, fraction));
		}

        virtual int serialize( ostream &stream );
        virtual int deserialize( istream &stream );

		// Get the distance to another point
		virtual inline float getDistanceTo( const Vector2& other ) const { return sqrt(getDistanceToSquared(other)); }
		// Get the distance to another point squared
        virtual float getDistanceToSquared( const Vector2& other ) const;

		// Get the length of the vector
		virtual inline float getLength( void ) const { return sqrt(getLengthSquared()); }
		// Get the length of the vector squared
		virtual inline float getLengthSquared( void ) const { return (X * X) + (Y * Y); }

		// Get the angle of the direction to the other point
		virtual Angle getAngleTo( const Vector2& other ) const;
		// Get the angle of the direction to the other point in radians
		virtual inline float getAngleToRad( const Vector2& other ) const { return atan2(other.Y - Y, other.X - X); }
		// Get the angle of the direction to the other point in degrees
		virtual inline float getAngleToDeg( const Vector2& other ) const  { return toDeg(getAngleToRad(other)); }

		// Get the dot product of this and the other vector
		inline float getDot( const Vector2& rhs ) const { return (X * rhs.X) + (Y * rhs.Y); }
		// Normalizes the vector and stores the new values in X and Y
		virtual void normalize( void );

        virtual inline float getHalfX( void ) const { return (X * 0.5f); }
        virtual inline float getHalfY( void ) const { return (Y * 0.5f); }

		// Functions to treat X and Y as Width and Height for Size

        virtual inline float getWidth ( void ) const { return X; }
        virtual inline float getHeight( void ) const { return Y; }
        virtual inline float getHalfWidth ( void ) const { return getHalfX(); }
        virtual inline float getHalfHeight( void ) const { return getHalfY(); }

        const Vector2 operator+( const Vector2& rhs ) const;
		const Vector2 operator-( const Vector2& rhs ) const;
		const Vector2 operator*( const Vector2& rhs ) const;
		const Vector2 operator/( const Vector2& rhs ) const;
        const Vector2 operator*( float value ) const;
        const Vector2 operator/( float value ) const;

        Vector2& operator+=( const Vector2& rhs );
		Vector2& operator-=( const Vector2& rhs );
		Vector2& operator*=( const Vector2& rhs );
		Vector2& operator/=( const Vector2& rhs );
        Vector2& operator*=( float value );
        Vector2& operator/=( float value );
        Vector2& operator= ( const Vector2& rhs );

        bool operator==( const Vector2& rhs ) const;
		bool operator!=( const Vector2& rhs ) const;

		bool operator<( const Vector2& rhs ) const;
		bool operator>( const Vector2& rhs ) const;
		bool operator<=( const Vector2& rhs ) const;
		bool operator>=( const Vector2& rhs ) const;

    }; // class Vector2

    struct CompVector2
        : public std::binary_function<Vector2, Vector2, bool>
    {
        inline bool operator()(const Vector2& lhs, const Vector2& rhs) const
        {
            return lhs.X < rhs.X; // Simple Sorting
        }

    }; // struct CompVector2

} // namespace Arc

#endif // __ARC_VECTOR_2_H__
