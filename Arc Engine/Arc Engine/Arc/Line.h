#pragma once

#ifndef __ARC_LINE_H__
#define __ARC_LINE_H__

#include "GameObject.h"

#include "Vector2.h"

namespace Arc
{
    class Line :
        public GameObject
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

        virtual string toString( void ) const { return "Line"; }

        float length( void ) { return A.distanceTo(B); }

        float angleAtoBDeg( void ) { A.angleToDeg(B); }
        float angleBtoADeg( void ) { B.angleToDeg(A); }

        float angleAtoBRad( void ) { A.angleToRad(B); }
        float angleBtoARad( void ) { B.angleToRad(A); }

        Point lerp   ( float fraction ) { return A.lerp(B, fraction); }
        Point lerpRev( float fraction ) { return B.lerp(A, fraction); }

        Line& operator= ( const Line& rhs );

        bool operator==( const Line& rhs ) const;
        bool operator!=( const Line& rhs ) const;

    }; // class Line

} // namespace Arc

#endif // __ARC_LINE_H__