#pragma once

#ifndef __ARC_MATH_FUNC_H__
#define __ARC_MATH_FUNC_H__

#include <cmath>
#include "Direction.h"

namespace Arc
{
    class Vector2;




    bool linesIntersect( Vector2 L1P1, Vector2 L1P2, Vector2 L2P1, Vector2 L2P2 );

    Direction angleRadToDir     ( float angle );
    Direction angleRadToDirEight( float angle );
    Direction angleRadToDirFour ( float angle );

    Direction angleDegToDir     ( float angle );
    Direction angleDegToDirEight( float angle );
    Direction angleDegToDirFour ( float angle );

} // namespace Arc

#endif // __ARC_MATH_FUNC_H__
