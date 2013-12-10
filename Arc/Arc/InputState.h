#pragma once

#ifndef __ARC_INPUT_STATE_H__
#define __ARC_INPUT_STATE_H__

#include "Common.h"
#include "ManagedObject.h"

namespace Arc
{
    struct InputState
        : public ManagedObject
    {
        bool
            Pressed,
            Released,
            Down,
            Tapped;

        InputState( bool pressed = false, bool released = false, bool down = false, bool tapped = false )
			: Pressed(pressed),
			  Released(released),
			  Down(down),
			  Tapped(tapped)
        {
        }

        virtual inline string toString( void ) const { return "Input State"; }

    }; // struct InputState

} // namespace Arc

#endif
