#pragma once

#ifndef __ARC_INPUT_SYSTEM_H__
#define __ARC_INPUT_SYSTEM_H__

#include "Common.h"
#include "SystemComponent.h"

#include <SDL/SDL.h>

#include "Mouse.h"
#include "Keyboard.h"
#include "GamePad.h"
#include "InputState.h"

#include "KeyboardSource.h"
#include "MouseSource.h"

namespace Arc
{
	class GraphicalProgram;

    class InputSystem :
        public SystemComponent
    {
		
		friend class GraphicalProgram;

    protected:

		// Manager for keyboard input
        KeyboardSource* _pKeyboardSource;

		// Manager for mouse input
        MouseSource* _pMouseSource;

		// Function for handling the SDL Event loop
        virtual void handleSDLEvent( SDL_Event sdlEvent );

    public:

		static const SystemComponentType SYS_CMP_TYPE_INPUT;

        InputSystem( Program* pProgram );
        virtual ~InputSystem( void );

        virtual inline string toString( void ) const { return "Input System"; }

        virtual void eventUpdate( const Event& event );

    }; // class InputSystem

} // namespace Arc

#endif // __ARC_INPUT_SYSTEM_H__
