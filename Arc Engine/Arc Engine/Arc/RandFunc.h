#pragma once

#ifndef __ARC_RAND_FUNC_H__
#define __ARC_RAND_FUNC_H__

#include <cstdlib>
#include <ctime>

namespace Arc
{
    void initRandom( void );

    int    randInt   ( int    min, int    max );
    float  randFloat ( float  min, float  max );
    double randDouble( double min, double max );

} // namespace Arc

#endif // __ARC_RAND_FUNC_H__
