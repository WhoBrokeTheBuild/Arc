#include "MathFunc.h"
#include "Vector2.h"
#include "Direction.h"

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

Arc::Direction Arc::angleRadToDir( float angle )
{
    return angleRadToDirEight(angle);
}

Arc::Direction Arc::angleRadToDirEight( float angle )
{
    return angleDegToDirEight(toDeg(angle));
}

Arc::Direction Arc::angleRadToDirFour( float angle )
{
    return angleDegToDirFour(toDeg(angle));
}

Arc::Direction Arc::angleDegToDir( float angle )
{
    return angleDegToDirEight(angle);
}

Arc::Direction Arc::angleDegToDirEight( float angle )
{
    angle = abs(angle);

    float check = 67.5f;
    Direction dir = DIR_NORTH;
    for (unsigned int i = 0; i < 8; ++i)
    {
        float checkEnd = check + 45.0f;
        if (checkEnd >= 360.0f)
            checkEnd -= 360.0f;

        if (between(angle, check, checkEnd))
        {
            return dir;
        }

        dir = (Direction)(dir + 1);
        check += 45.0f;
        if (check >= 360.0f)
            check -= 360.0f;
    }

    return INVALID_DIRECTION;
}

Arc::Direction Arc::angleDegToDirFour( float angle )
{
    angle = abs(angle);

    if (between(angle, 45.0f, 135.0f))
    {
        return DIR_NORTH;
    }
    else if (between(angle, 135.0f, 225.0f))
    {
        return DIR_WEST;
    }
    else if (between(angle, 225.0f, 315.0f))
    {
        return DIR_SOUTH;
    }
    else if (between(angle, 315.0f, 0.0f) || between(angle, 0.0f, 45.0f))
    {
        return DIR_EAST;
    }

    return INVALID_DIRECTION;
}
