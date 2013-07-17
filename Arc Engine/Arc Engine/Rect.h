#pragma once

#ifndef __RECT_H__
#define __RECT_H__

#include "GameObject.h"
#include "Vector2.h"

class Circle;

class Rect
    : public GameObject
{
private:

public:

    static Rect
        ZERO,
        ONE;

    float 
        X,
        Y,
        Width,
        Height;

    Rect( void );
    Rect( float x, float y, float width, float height );
    Rect( Vector2 pos, Size size );
    virtual ~Rect( void );

    virtual string toString( void ) const;

    void setPos( Vector2 pos );
    void setSize( Size size );

    float halfWidth ( void ) const { return Width * 0.5f; }
    float halfHeight( void ) const { return Height * 0.5f; }

    inline Vector2 center( void ) const { return Vector2( X + halfWidth(), Y + halfHeight() ); }

    inline Vector2 pos ( void ) const { return Vector2( X, Y ); }
    inline Size    size( void ) const { return Vector2( Width, Height ); }

    inline float top   ( void ) const { return Y; }
    inline float bottom( void ) const { return Y + Height; }
    inline float left  ( void ) const { return X; }
    inline float right ( void ) const { return X + Width; }

    bool containsRect  ( Rect other ) const;
    bool containsCircle( Circle other ) const;
    bool containsPoint ( Vector2 point ) const;

    const Rect operator+( const Rect &rhs ) const;
    const Rect operator-( const Rect &rhs ) const;

    Rect &operator+=( const Rect &rhs );
    Rect &operator-=( const Rect &rhs );

    bool operator==( const Rect &rhs ) const;
    bool operator!=( const Rect &rhs ) const;

};

struct CompRect 
    : public binary_function<Rect, Rect, bool>
{
    bool operator()(const Rect& lhs, const Rect& rhs) const
    {
        return lhs.X < rhs.X; // Simple Sorting
    }
};

#endif 