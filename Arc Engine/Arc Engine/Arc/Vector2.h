#pragma once

#ifndef __ARC_VECTOR_2_H__
#define __ARC_VECTOR_2_H__

#include "GameObject.h"
#include "Functions.h"

namespace Arc
{
    class Vector2;

    typedef Vector2 Point;
    typedef Vector2 Size;

    class Vector2
        : public GameObject
    {
    public:

        static Vector2
            ZERO,
            ONE,
            NEGATIVE_ONE;

        float
            X,
            Y;

        Vector2( void ) { X = Y = 0; }

        Vector2( float x, float y )
        {
            X = x;
            Y = y;
        }

        Vector2( float both )
        {
            X = both;
            Y = both;
        }

        virtual ~Vector2( void ) { }

        virtual string toString( void ) const;

        float distanceTo( Vector2 other );
        float angleToDeg( Vector2 other );
        float angleToRad( Vector2 other );

        float halfX( void ) { return (X * 0.5f); }
        float halfY( void ) { return (Y * 0.5f); }

        float width ( void ) { return X; }
        float height( void ) { return Y; }
        float halfWidth ( void ) { return halfX(); }
        float halfHeight( void ) { return halfY(); }

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
        bool operator()(const Vector2& lhs, const Vector2& rhs) const
        {
            return lhs.X < rhs.X; // Simple Sorting
        }

    }; // struct CompVector2

} // namespace Arc

#endif // __ARC_VECTOR_2_H__
