#pragma once

#ifndef __ARC_MOUSE_H__
#define __ARC_MOUSE_H__

#include <string>
#include <SDL/SDL.h>

using std::string;

namespace Arc
{
    const int
        MOUSE_WHEEL_DOWN = 4,
        MOUSE_WHEEL_UP   = 5;

    enum MouseButton
    {
        INVALID_MOUSE_BUTTON = -1,

        MOUSE_BUTTON_LEFT,
        MOUSE_BUTTON_MIDDLE,
        MOUSE_BUTTON_RIGHT,

        NUM_MOUSE_BUTTONS

    }; // enum MouseButton

    const string MOUSE_BUTTON_NAMES[NUM_MOUSE_BUTTONS] =
    {
        "Left Button",
        "Middle Button",
        "Right Button"
    };

} // namespace Arc

#endif // __ARC_MOUSE_H__
