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

        Circle( void ) { X = Y = Radius = 0.0f; }
        Circle( float x, float y, float radius );
        Circle( Point pos, float radius );
        virtual ~Circle( void ) { }

        virtual inline string toString( void ) const
        {
            stringstream ss;
            ss << "Circle [X: " << X << ", Y: " << Y << ", R:" << Radius << "]";
            return ss.str();
        }

        virtual int serialize( ostream &stream );
        virtual int deserialize( istream &stream );

        inline Point pos ( void ) { return Point(X, Y); }
        inline Point center( void ) { return Point(X + Radius, Y + Radius); }

        inline float diameter( void ) { return Radius * 2.0f; }

        inline float top   ( void ){ return Y; }
        inline float bottom( void ){ return Y + diameter(); }
        inline float left  ( void ){ return X; }
        inline float right ( void ){ return X + diameter(); }

        Rect bounds( void );

        bool containsCircle(Circle other);
        bool containsRect  (Rect   other);
        bool containsPoint (Point  point);

    };
}

#endif
