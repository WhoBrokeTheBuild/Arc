#pragma once

#ifndef __ARC_MATH_FUNC_H__
#define __ARC_MATH_FUNC_H__

#include <cmath>

namespace Arc
{
    class Vector2;
    enum Direction;

    #define PI  3.14159
    #define PI2 6.28318

    #define TO_RAD (PI / 180.0)
    #define TO_DEG (180.0 / PI)

    inline float toRad( int deg ) { return (float)( deg * TO_RAD ); }
    inline float toDeg( int rad ) { return (float)( rad * TO_DEG ); };

    inline float toRad( float deg ) { return (float)( deg * TO_RAD ); }
    inline float toDeg( float rad ) { return (float)( rad * TO_DEG ); };

    inline double toRad( double deg ) { return (double)( deg * TO_RAD ); }
    inline double toDeg( double rad ) { return (double)( rad * TO_DEG ); };

    float floor  (float value, int accuracy);
    float nearest(float value, int accuracy);
    float ceil   (float value, int accuracy);

    double floor  (double value, int accuracy);
    double nearest(double value, int accuracy);
    double ceil   (double value, int accuracy);

    template <class Number>
    Number clamp(Number value, Number min, Number max) { return ( ( value > max ) ? max : ( ( value < min ) ? min : value ) ); }

    template <class Number>
    int sign( Number value ) { return ( value > 0 ? 1 : ( value < 0 ? -1 : 0 ) ); }

    template <class Number>
    Number approach( Number value, Number target, Number speed ) { return ( ( value > target ) ? max( value - speed, target ) : min( value + speed, target ) ); }

    template <class Number>
    Number reduce( Number value, Number speed ) { return ( ( value > 0 ) ? max( value - speed, 0 ) : min( value + speed, 0 ) ); }

    template <class Number>
    bool between( Number value, Number min, Number max ) { return ( value >= min && value <= max); }

    template <class Number>
    Number lerp( Number start, Number end, float fraction) { return ( start + (end - start) * fraction ); }

    // Source: http://paulbourke.net/miscellaneous/interpolation/
    // Tension: 1 is high, 0 normal, -1 is low
    // Bias: 0 is even, positive is towards first segment, negative towards the other
    template <class Number>
    Number hermite( Number x0, Number x1, Number x2, Number x3, Number mu, double tension, double bias)
    {
        Number m0, m1, mu2, mu3;
        Number a0, a1, a2, a3;

        mu2 = mu * mu;
        mu3 = mu2 * mu;
        m0  = (x1 - x0) * (1 + bias) * (1 - tension) / 2;
        m0 += (x2 - x1) * (1 - bias) * (1 - tension) / 2;
        m1  = (x2 - x1) * (1 + bias) * (1 - tension) / 2;
        m1 += (x3 - x2) * (1 - bias) * (1 - tension) / 2;
        a0 =  2 * mu3 - 3 * mu2 + 1;
        a1 =      mu3 - 2 * mu2 + mu;
        a2 =      mu3 -     mu2;
        a3 = -2 * mu3 + 3 * mu2;

        return (a0 * x1 + a1 * m0 + a2 * m1 + a3 * x2);
    }

    bool linesIntersect( Vector2 L1P1, Vector2 L1P2, Vector2 L2P1, Vector2 L2P2 );

    Direction angleRadToDir     ( float angle );
    Direction angleRadToDirEight( float angle );
    Direction angleRadToDirFour ( float angle );

    Direction angleDegToDir     ( float angle );
    Direction angleDegToDirEight( float angle );
    Direction angleDegToDirFour ( float angle );

} // namespace Arc

#endif // __ARC_MATH_FUNC_H__
