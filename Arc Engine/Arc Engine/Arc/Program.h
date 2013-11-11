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
	/** The control class for the entire program. Handles the update and render loops,
	  * as well as storing all of the system class instances.
	  */
    class Program :
        public EventDispatcher
    {
    protected:

		// A static instance used to access the instances of the managers
        static Program* _pInstance;

		// A system for managing the window and drawing
        GraphicsSystem* _pGraphicsSystem;

		// A system for managing the keyboard, mouse, and game pad input
        InputSystem* _pInputSystem;

		// A system for managing the playing and looping of audio
        AudioSystem* _pAudioSystem;

		// A system for managing and interfacing with Lua
        ScriptingSystem* _pScriptingSystem;

		// A system for managing sockets and connections
        NetworkSystem* _pNetworkSystem;

		// Whether the program is supposed to be running or not
        bool _running; 

		// The FPS the program is trying to run at
        float _targetFPS;

		// The FPS the program is currently running at
		float _currentFPS;

    public:

		// The pre-update event type
        static const EventType EVENT_UPDATE_START;
		
		// The update event type
		static const EventType EVENT_UPDATE;

		// The post-update event type
		static const EventType EVENT_UPDATE_END;

		// The pre-render event type
		static const EventType EVENT_RENDER_START;

		// The render event type
		static const EventType EVENT_RENDER;

		// The post-render event type
		static const EventType EVENT_RENDER_END;

		// The event called to end the program
		static const EventType EVENT_EXIT;

		Program( void );
		virtual ~Program( void );

        virtual inline string toString( void ) const { return "Program"; }

		/* Gets the static instance the program singleton
		 *
		 * @returns: The static instance to the program singleton
		 */
        static Program* getInstance( void ) { return _pInstance; }

		/* Start the program and the begin update/render loop
		 */
        virtual void start( void );

		/* Trigger a flag to stop the update/render loop in response to an EVENT_EXIT event
		 * 
		 * @param event: Unused event data
		 */
        virtual void stop ( const Event& event );

		/* Sends out the EVENT_UPDATE_START, EVENT_UPDATE, and EVENT_UPDATE_END events in that order
		 * 
		 * @param frameData: The frame data to send to the update events, includes timing and framerate information
		 */
        virtual void updateFrame( const FrameData&  frameData );
		
		/* Send out the EVENT_RENDER_START, EVENT_RENDER, and EVENT_RENDER_END events in that order
		 * 
		 * @param renderData: The render data to send to the render events, includes access to the render target
		 */
        virtual void renderFrame( const RenderData& renderData );

		/* Initializes all systems
		 * 
		 * @param windowSize: The size of the window to be created
		 * @param windowTitle: The text to show at the top of the window
		 * @param clearColor: The color to clear the window to at the start of every frame
		 *		default: Color::BLACK
		 */
        virtual void initAll( Size windowSize, string windowTitle, Color clearColor = Color::BLACK );
		
		/* Initialize the core underlying systems 
		 */
        virtual void initCore( void );

		/* Initialize the graphics system and create the window
		 * 
		 * @param windowSize: The size of the window to be created
		 * @param windowTitle: The text to show at the top of the window
		 * @param clearColor: The color to clear the window to at the start of every frame
		 *		default: Color::BLACK
		 */
        virtual void initGraphics( Size windowSize, string windowTitle, Color clearColor = Color::BLACK);

		/* Initialize the audio system
		 */
        virtual void initAudio( void );

		/* Initialize the input system
		 */
        virtual void initInput( void );

		/* Initialize the scripting system
		 */
        virtual void initScripting ( void );
		
		/* Initialize the networking system
		 */
        virtual void initNetworking( void );
		
		/* Access the graphics system
		 * 
		 * @returns: A pointer to the graphics system
		 */
        inline GraphicsSystem* getGraphicsSystem( void ) { return _pGraphicsSystem; }
		
		/* Access the input system
		 * 
		 * @returns: A pointer to the input system
		 */
        inline InputSystem* getInputSystem( void ) { return _pInputSystem; }
		
		/* Access the audio system
		 * 
		 * @returns: A pointer to the audio system
		 */
        inline AudioSystem* getAudioSystem( void ) { return _pAudioSystem; }
		
		/* Access the scripting system
		 * 
		 * @returns: A pointer to the scripting system
		 */
        inline ScriptingSystem* getScriptingSystem( void ) { return _pScriptingSystem; }
		
		/* Access the network system
		 * 
		 * @returns: A pointer to the network system
		 */
        inline NetworkSystem* getNetworkSystem( void ) { return _pNetworkSystem; }
		
		/* Callback triggered before the update event
		 * 
		 * @param event: The event information, including the FrameData as the data
		 */
		virtual void updateStart( const Event& event ) { }
		
		/* Callback triggered during the update event
		 * 
		 * @param event: The event information, including the FrameData as the data
		 */
        virtual void update( const Event& event ) { }
		
		/* Callback triggered after the update event
		 * 
		 * @param event: The event information, including the FrameData as the data
		 */
		virtual void updateEnd( const Event& event ) { }
		
		/* Callback triggered before the render event
		 * 
		 * @param event: The event information, including the RenderData as the data
		 */
		virtual void renderStart( const Event& event ) { }
		
		/* Callback triggered during the render event
		 * 
		 * @param event: The event information, including the RenderData as the data
		 */
        virtual void render( const Event& event ) { }
		
		/* Callback triggered after the render event
		 * 
		 * @param event: The event information, including the RenderData as the data
		 */
		virtual void renderEnd( const Event& event ) { }

    }; // class Program

} // namespace Arc

#endif // __ARC_PROGRAM_H__
