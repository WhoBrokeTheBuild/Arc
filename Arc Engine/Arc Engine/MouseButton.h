#pragma once

#ifndef __MOUSE_BUTTONS_H__
#define __MOUSE_BUTTONS_H__

#include "ArcCommon.h"

enum MouseButton
{
    INVALID_MOUSE_BUTTON = -1,
    MOUSE_BUTTON_LEFT,
    MOUSE_BUTTON_MIDDLE,
    MOUSE_BUTTON_RIGHT,
    NUM_MOUSE_BUTTONS
};

const string MOUSE_BUTTON_NAMES[NUM_MOUSE_BUTTONS] = {
    "Left Button",
    "Middle Button",
    "Right Button"
};

#endif