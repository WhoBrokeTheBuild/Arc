#pragma once

#ifndef __ARC_DIRECTION_H__
#define __ARC_DIRECTION_H__

#include <string>

using std::string;

namespace Arc
{
    enum Direction
    {
        INVALID_DIRECTION = -1,

        DIR_NORTH,
        DIR_NORTH_WEST,
        DIR_WEST,
        DIR_SOUTH_WEST,
        DIR_SOUTH,
        DIR_SOUTH_EAST,
        DIR_EAST,
        DIR_NORTH_EAST,

        NUM_DIRECTIONS

    }; // enum Direction

    const string DIRECTION_NAMES[NUM_DIRECTIONS] =
    {
        "North",
        "North West",
        "West",
        "South West",
        "South",
        "South East",
        "East",
        "North East"
    };

} // namespace Arc

#endif // __ARC_DIRECTION_H__
