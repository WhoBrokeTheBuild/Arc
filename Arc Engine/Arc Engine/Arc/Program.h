#pragma once

#ifndef __ARC_PROGRAM_H__
#define __ARC_PROGRAM_H__

#include "Common.h"
#include "EventDispatcher.h"

#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_opengl.h>

#include "GraphicsSystem.h"
#include "InputSystem.h"
#include "AudioSystem.h"
#include "ScriptingSystem.h"
#include "NetworkSystem.h"

#include "RenderTarget.h"
#include "Animation.h"
#include "Sprite.h"
#include "Texture.h"
#include "RenderedText.h"
#include "Timer.h"

namespace Arc
{
	/** This is the control class for the entire program. It handles the update and render loops,
	  * as well as storing all of the system class instances.
	  */
    class Program :
        public EventDispatcher
    {
    protected:

		// A static instance used to access the instances of the managers
        static Program
            *_pInstance;

		// A system for managing the window and drawing
        GraphicsSystem
            *_pGraphicsSystem;

		// A system for managing the keyboard, mouse, and game pad input
        InputSystem
            *_pInputSystem;

		// A system for managing the playing and looping of audio
        AudioSystem
            *_pAudioSystem;

		// A system for managing and interfacing with Lua
        ScriptingSystem
            *_pScriptingSystem;

		// A system for managing sockets and connections
        NetworkSystem
            *_pNetworkSystem;

        bool
            _running; // Whether the game is supposed to be running or not

        float
            _targetFPS,
            _currentFPS;

    public:

        static const EventType
            EVENT_UPDATE_START,
            EVENT_UPDATE,
            EVENT_UPDATE_END,
            EVENT_RENDER_START,
            EVENT_RENDER,
            EVENT_RENDER_END,
            EVENT_EXIT;

        Program( void );
        virtual ~Program( void );

        virtual inline string toString( void ) const { return "Program"; }

		// Get the static instance of the class
        static Program* getInstance( void ) { return _pInstance; }

        virtual void start( void );
        virtual void stop ( const Event& event );

        virtual void updateFrame( const FrameData&  frameData );
        virtual void renderFrame( const RenderData& renderData );

        virtual void initAll       ( Size windowSize, string windowTitle, Color clearColor = Color::BLACK );
        virtual void initCore      ( void );
        virtual void initGraphics  ( Size windowSize, string windowTitle, Color clearColor = Color::BLACK);
        virtual void initAudio     ( void );
        virtual void initInput     ( void );
        virtual void initScripting ( void );
        virtual void initNetworking( void );

        inline GraphicsSystem*  getGraphicsSystem ( void ) { return _pGraphicsSystem; }
        inline InputSystem*     getInputSystem    ( void ) { return _pInputSystem; }
        inline AudioSystem*     getAudioSystem    ( void ) { return _pAudioSystem; }
        inline ScriptingSystem* getScriptingSystem( void ) { return _pScriptingSystem; }
        inline NetworkSystem*   getNetworkSystem  ( void ) { return _pNetworkSystem; }

        virtual void update( const Event& event ) { };
        virtual void render( const Event& event ) { };

    }; // class Program

} // namespace Arc

#endif // __ARC_PROGRAM_H__
