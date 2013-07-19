#pragma once

#ifndef __ARC_INPUT_FUNC_H__
#define __ARC_INPUT_FUNC_H__

#include "Keyboard.h"
#include "Mouse.h"
#include <SDL/SDL.h>

namespace Arc
{
    KeyboardKey SDLKeyToKey( SDLKey sdlKey );
    SDLKey      KeyToSDLKey( KeyboardKey key );
    char        KeyToChar  ( KeyboardKey key, bool shift = false );

    MouseButton SDLMouseToMouse( int sdlButton );
    int         MouseToSDLMouse( MouseButton button );
}

#endif
