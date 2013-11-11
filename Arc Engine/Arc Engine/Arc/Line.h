#pragma once

#ifndef __ARC_LINE_H__
#define __ARC_LINE_H__

#include "ManagedObject.h"
#include "ISerializable.h"
#include "Functions.h"

#include "Vector2.h"

namespace Arc
{
    class Angle;

    class Line :
        public ManagedObject,
        public ISerializable
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

        virtual inline string toString( void ) const
        {
            stringstream ss;
            ss << "Line [A: [" << A.X << ", " << A.Y << "], B: [" << B.X << ", " << B.Y << "] ]";
            return ss.str();
        }

        virtual int serialize( ostream &stream );
        virtual int deserialize( istream &stream );

        inline float length( void ) { return A.getDistanceTo(B); }

        inline float angleAtoBDeg( void ) { return A.getAngleToPointDeg(B); }
        inline float angleBtoADeg( void ) { return B.getAngleToPointDeg(A); }

        inline float angleAtoBRad( void ) { return A.getAngleToPointRad(B); }
        inline float angleBtoARad( void ) { return B.getAngleToPointRad(A); }

        inline Angle angleAtoB( void );
        inline Angle angleBtoA( void );

        inline Point lerp   ( float fraction ) { return Vector2::lerp(A, B, fraction); }
        inline Point lerpRev( float fraction ) { return Vector2::lerp(B, A, fraction); }

        Line& operator= ( const Line& rhs );

        bool operator==( const Line& rhs ) const;
        bool operator!=( const Line& rhs ) const;

    }; // class Line

} // namespace Arc

#endif // __ARC_LINE_H__
