#pragma once

#ifndef __ARC_INPUT_SOURCE_TYPE_H__
#define __ARC_INPUT_SOURCE_TYPE_H__

#include <string>

using std::string;

namespace Arc
{
    enum InputSourceType
    {
        INVALID_INPUT_SOURCE_TYPE = -1,

        INPUT_SOURCE_TYPE_KEYBOARD,
        INPUT_SOURCE_TYPE_MOUSE,
        INPUT_SOURCE_TYPE_GAME_PAD,

        NUM_INPUT_SOURCE_TYPES

    }; // enum InputSourceType

    const string INPUT_SOURCE_TYPE_NAMES[NUM_INPUT_SOURCE_TYPES] =
    {
        "Keyboard",
        "Mouse",
        "Game Pad"
    };

} // namespace Arc

#endif // __ARC_INPUT_SOURCE_TYPE_H__
