#include "MathFunc.h"
#include "Vector2.h"

float Arc::floor( float value, int accuracy )
{
    int mult = 10 * accuracy; 
    return std::floorf(value * mult) / mult;
}

double Arc::floor( double value, int accuracy )
{
    int mult = 10 * accuracy;
    return std::floor(value * mult) / mult;
}

float Arc::nearest( float value, int accuracy )
{
    int mult = 10 * accuracy;
    return std::floorf(value * mult + 0.5f) / mult;
}

double Arc::nearest( double value, int accuracy )
{
    int mult = 10 * accuracy;
    return std::floor(value * mult + 0.5) / mult;
}

float Arc::ceil( float value, int accuracy )
{
    int mult = 10 * accuracy;
    return std::ceilf(value * mult) / mult;
}

double Arc::ceil( double value, int accuracy )
{
    int mult = 10 * accuracy;
    return std::ceil(value * mult) / mult;
}

bool Arc::linesIntersect( Vector2 L1P1, Vector2 L1P2, Vector2 L2P1, Vector2 L2P2 )
{
    float 
        ua = 0,
        ub = 0,
        ud = (L2P2.Y - L2P1.Y) * (L1P2.X - L1P1.X) - (L2P2.X - L2P1.X) * (L1P2.Y - L1P1.Y);

    if (ud != 0)
    {
        ua = ((L2P2.X - L2P1.X) * (L1P1.Y - L2P1.Y) - (L2P2.Y - L2P1.Y) * (L1P1.X - L2P1.X)) / ud;
        ub = ((L1P2.X - L1P1.X) * (L1P1.Y - L2P1.Y) - (L1P2.Y - L1P1.Y) * (L1P1.X - L2P1.X)) / ud;

        if (ua < 0 || ua > 1 || ub < 0 || ub > 1)
            ua = 0;
    }

    return ua != 0;
}