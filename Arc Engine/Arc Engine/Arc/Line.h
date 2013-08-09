#pragma once

#ifndef __ARC_LINE_H__
#define __ARC_LINE_H__

#include "ManagedObject.h"

#include "Vector2.h"

namespace Arc
{
    class Angle;

    class Line :
        public ManagedObject
    {
    public:

        Point
            A,
            B;

        static Line
            ZERO;

        Line( void ) { A = B = Vector2::ZERO; }

        Line( Point a, Point b )
        { 
            A = a;
            B = b;
        }

        Line( float aX, float aY, float bX, float bY )
        {
            A = Point(aX, aY);
            B = Point(bX, bY);
        }

        virtual ~Line(void) { }

        virtual inline string toString( void ) const { return "Line"; }

        inline float length( void ) { return A.distanceTo(B); }

        inline float angleAtoBDeg( void ) { A.angleToDeg(B); }
        inline float angleBtoADeg( void ) { B.angleToDeg(A); }

        inline float angleAtoBRad( void ) { A.angleToRad(B); }
        inline float angleBtoARad( void ) { B.angleToRad(A); }

        inline Angle angleAtoB( void );
        inline Angle angleBtoA( void );

        inline Point lerp   ( float fraction ) { return A.lerp(B, fraction); }
        inline Point lerpRev( float fraction ) { return B.lerp(A, fraction); }

        Line& operator= ( const Line& rhs );

        bool operator==( const Line& rhs ) const;
        bool operator!=( const Line& rhs ) const;

    }; // class Line

} // namespace Arc

#endif // __ARC_LINE_H__