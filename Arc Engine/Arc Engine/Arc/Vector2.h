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

    typedef Vector2 Point;
    typedef Vector2 Size;

    class Vector2
        : public ManagedObject,
          public ISerializable
    {
    public:

        static Vector2
            ZERO,
            ONE,
            NEGATIVE_ONE;

        float
            X,
            Y;

        inline Vector2( void ) { X = Y = 0.0f; }
		inline Vector2( float both ) { X = Y = both; }
        inline Vector2( float x, float y ) { X = x; Y = y; }

        virtual inline ~Vector2( void ) { }

        virtual inline string toString( void ) const
        {
            stringstream ss;
            ss << "Vector2 [X: " << X << ", Y: " << Y << "]";
            return ss.str();
        }

		inline static Vector2 rand( float minX, float minY, float maxX, float maxY )
		{
			return Vector2(randFloat(minX, maxX), randFloat(minY, maxY));
		}

        virtual int serialize( ostream &stream );
        virtual int deserialize( istream &stream );

        inline float distanceToSquared( Vector2 other )
        {
            float dx = other.X - X,
                  dy = other.Y - Y;

            return (dx * dx + dy * dy);
        }

        inline float angleToRad( Vector2 other )
        {
            float dx = other.X - X,
                  dy = other.Y - Y;

            return atan2(dy, dx);
        }

        inline float distanceTo( Vector2 other ) { return sqrt(distanceToSquared(other)); }
        inline float angleToDeg( Vector2 other ) { return toDeg(angleToRad(other)); }

        Angle angleTo( Vector2 other );

        float halfX( void ) { return (X * 0.5f); }
        float halfY( void ) { return (Y * 0.5f); }

        inline float width ( void ) { return X; }
        inline float height( void ) { return Y; }
        inline float halfWidth ( void ) { return halfX(); }
        inline float halfHeight( void ) { return halfY(); }

        Vector2 lerp      ( const Vector2& other, float fraction );
		Vector2 normLeft  ( const Vector2& other );
		Vector2 normRright( const Vector2& other );
		float   dot       ( const Vector2& rhs );

        const Vector2 operator+( const Vector2& rhs ) const;
        const Vector2 operator-( const Vector2& rhs ) const;
        const Vector2 operator*( float value ) const;
        const Vector2 operator/( float value ) const;

        Vector2& operator+=( const Vector2& rhs );
        Vector2& operator-=( const Vector2& rhs );
        Vector2& operator*=( float value );
        Vector2& operator/=( float value );
        Vector2& operator= ( const Vector2& rhs );

        bool operator==( const Vector2& rhs ) const;
        bool operator!=( const Vector2& rhs ) const;

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
