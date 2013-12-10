#pragma once

#ifndef __ARC_MATH_FUNC_H__
#define __ARC_MATH_FUNC_H__

#include <cmath>

namespace Arc
{
    class Vector2;

    bool linesIntersect( Vector2 L1P1, Vector2 L1P2, Vector2 L2P1, Vector2 L2P2 );

} // namespace Arc

#endif // __ARC_MATH_FUNC_H__
