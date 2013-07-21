#pragma once

#ifndef __ARC_INPUT_TYPE_H__
#define __ARC_INPUT_TYPE_H__

#include <string>

using std::string;

namespace Arc
{
    enum InputType
    {
        INVALID_INPUT_TYPE = -1,

        INPUT_TYPE_PRESSED,
        INPUT_TYPE_RELEASED,
        INPUT_TYPE_HELD,
        INPUT_TYPE_OTHER,

        NUM_INPUT_TYPES

    }; // enum InputType

    const string INPUT_TYPE_NAMES[NUM_INPUT_TYPES] =
    {
        "Pressed",
        "Released",
        "Held",
        "Other"
    };

} // namespace Arc

#endif // __ARC_INPUT_TYPE_H__
