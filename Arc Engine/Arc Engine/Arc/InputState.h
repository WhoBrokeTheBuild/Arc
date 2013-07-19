#pragma once

#ifndef __ARC_INPUT_STATE_H__
#define __ARC_INPUT_STATE_H__

#include "Common.h"
#include "GameObject.h"

namespace Arc
{
    struct InputState
        : public GameObject
    {
        bool
            Pressed,
            Released,
            Down,
            Tapped;

        InputState( bool pressed = false, bool released = false, bool down = false, bool tapped = false )
        {
            Pressed  = pressed;
            Released = released;
            Down     = down;
            Tapped   = tapped;
        }

        virtual string toString( void ) const { return "Input State"; }
    };
}

#endif
