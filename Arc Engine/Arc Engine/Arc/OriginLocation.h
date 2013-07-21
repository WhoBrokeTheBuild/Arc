#pragma once

#ifndef __ORIGIN_LOCATION_H__
#define __ORIGIN_LOCATION_H__

#include <string>

using std::string;

namespace Arc
{
    enum OriginLocation
    {
        INVALID_ORIGIN_LOCATION = -1,

        ORIGIN_LOCATION_MANUAL,

        ORIGIN_LOCATION_TOP_LEFT,
        ORIGIN_LOCATION_TOP_RIGHT,
        ORIGIN_LOCATION_BOTTOM_LEFT,
        ORIGIN_LOCATION_BOTTOM_RIGHT,
        ORIGIN_LOCATION_CENTER,
        ORIGIN_LOCATION_TOP_CENTER,
        ORIGIN_LOCATION_BOTTOM_CENTER,
        ORIGIN_LOCATION_LEFT_CENTER,
        ORIGIN_LOCATION_RIGHT_CENTER,

        NUM_ORIGIN_LOCATIONS

    }; // enum OriginLocation

    const string ORIGIN_LOCATION_NAMES[NUM_ORIGIN_LOCATIONS] = 
    {
        "Manual",
        "Top Left",
        "Top Right",
        "Bottom left",
        "Bottom Right",
        "Center",
        "Top Center",
        "Bottom Center",
        "Left Center",
        "Right Center"
    };

} // namespace Arc

#endif // __ARC_ORIGIN_LOCATION_H__
