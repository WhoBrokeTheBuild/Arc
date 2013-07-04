#include "MathFunc.h"

float floor( float value, int accuracy )
{
    int mult = 10 * accuracy; 
    return floorf(value * mult) / mult;
}

double floor( double value, int accuracy )
{
    int mult = 10 * accuracy;
    return floor(value * mult) / mult;
}

float nearest( float value, int accuracy )
{
    int mult = 10 * accuracy;
    return floorf(value * mult + 0.5f) / mult;
}

double nearest( double value, int accuracy )
{
    int mult = 10 * accuracy;
    return floor(value * mult + 0.5) / mult;
}

float ceil( float value, int accuracy )
{
    int mult = 10 * accuracy;
    return ceilf (value * mult) / mult;
}

double ceil( double value, int accuracy )
{
    int mult = 10 * accuracy;
    return ceil (value * mult) / mult;
}
