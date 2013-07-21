#pragma once

#ifndef __ARC_INPUT_FUNC_H__
#define __ARC_INPUT_FUNC_H__

#include <SDL/SDL.h>

#include "Keyboard.h"
#include "Mouse.h"

namespace Arc
{
    KeyboardKey SDLKeyToKey( SDLKey sdlKey );
    SDLKey      KeyToSDLKey( KeyboardKey key );
    char        KeyToChar  ( KeyboardKey key, bool shift = false );

    MouseButton SDLMouseToMouse( int sdlButton );
    int         MouseToSDLMouse( MouseButton button );

} // namespace Arc

#endif // __ARC_INPUT_FUCN_H__
