#pragma once

#ifndef __GRAPHICAL_PROGRAM_H__
#define __GRAPHICAL_PROGRAM_H__

#include "Common.h"
#include "Program.h"

#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_opengl.h>

#include "GraphicsSystem.h"
#include "InputSystem.h"
#include "AudioSystem.h"

#include "RenderTarget.h"
#include "Animation.h"
#include "Sprite.h"
#include "Texture.h"
#include "RenderedText.h"
#include "Timer.h"

namespace Arc
{
	/* A program with an attached window that fires update/render events.
	 */
	class GraphicalProgram :
		public Program
	{
	protected:

		// Whether the program is supposed to be running or not
		bool _running; 

		// The FPS the program is trying to run at
		float _targetFPS;

		// The FPS the program is currently running at
		float _currentFPS;

		void initSDL( void );

		void termSDL( void );

		void processSDLEvents();

		virtual void initEventHandlers( void );

		virtual void termEventHandlers( void );

		/* Initialize the graphics system and create the window
		 * 
		 * @param windowSize: The size of the window to be created
		 *		default: Size(640.0f, 480.0f)
		 * @param windowTitle: The text to show at the top of the window
		 *		default: "Arc"
		 * @param clearColor: The color to clear the window to at the start of every frame
		 *		default: Color::BLACK
		 * @param fullscreen: Whether the window should start in fullscreen mode or not
		 *		default: false
		 */
        void initGraphicsSystem( Size windowSize = Size(640.0f, 480.0f), string windowTitle = "Arc", Color clearColor = Color::BLACK, bool fullscreen = false );
		
		/* Terminate the graphics system and close the window
		 */
        void termGraphicsSystem( void );
		
		/* Initialize the audio system
		 */
        void initAudioSystem( void );

		/* Terminate the input system
		 */
        void termInputSystem( void );

	public:

#pragma region Event Types

		static const EventType EVENT_GRAPHICS_SYSTEM_INITIALIZED;

		static const EventType EVENT_GRAPHICS_SYSTEM_TERMINATED;

		static const EventType EVENT_AUDIO_SYSTEM_INITIALIZED;

		static const EventType EVENT_AUDIO_SYSTEM_TERMINATED;

		static const EventType EVENT_INPUT_SYSTEM_INITIALIZED;

		static const EventType EVENT_INPUT_SYSTEM_TERMINATED;

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

#pragma endregion
		
		GraphicalProgram( Size windowSize = Size(640.0f, 480.0f), string windowTitle = "Arc", Color clearColor = Color::BLACK, bool fullscreen = false );

		virtual ~GraphicalProgram( void );

		/* Start the program and the begin update/render loop
		 */
        virtual void start( void );

		/* Trigger a flag to stop the update/render loop
		 */
        virtual void stop ( void );
		
		/* Sends out the EVENT_UPDATE_START, EVENT_UPDATE, and EVENT_UPDATE_END events in that order
		 * 
		 * @param frameData: The frame data to send to the update events, includes timing and frame rate information
		 */
        virtual void updateFrame( const FrameData&  frameData );
		
		/* Send out the EVENT_RENDER_START, EVENT_RENDER, and EVENT_RENDER_END events in that order
		 * 
		 * @param renderData: The render data to send to the render events, includes access to the render target
		 */
        virtual void renderFrame( const RenderData& renderData );
		
		/* Initialize the input system
		 */
        void initInputSystem( void );
		
		/* Terminate the audio system
		 */
        void termAudioSystem( void );

		virtual bool isGraphicsSystemActive( void ) const { return (GraphicalProgram::getGraphicsSystem() != nullptr); }
		virtual bool isAudioSystemActive( void ) const { return (GraphicalProgram::getAudioSystem() != nullptr); }
		virtual bool isInputSystemActive( void ) const { return (GraphicalProgram::getInputSystem() != nullptr); }
		
		/* 
		 * @returns: A pointer to the graphics system
		 */
		static inline GraphicsSystem* getGraphicsSystem( void )
		{
			return GraphicalProgram::getInstance()->getSystemOfType<GraphicsSystem>(GraphicsSystem::SYS_CMP_TYPE_GRAPHICS); 
		}
		
		/* 
		 * @returns: A pointer to the input system
		 */
		static inline InputSystem* getInputSystem( void )
		{
			return GraphicalProgram::getInstance()->getSystemOfType<InputSystem>(InputSystem::SYS_CMP_TYPE_INPUT); 
		}
		
		/* 
		 * @returns: A pointer to the audio system
		 */
		static inline AudioSystem* getAudioSystem( void )
		{
			return GraphicalProgram::getInstance()->getSystemOfType<AudioSystem>(AudioSystem::SYS_CMP_TYPE_AUDIO); 
		}
		
		/*
		 * @returns: The Frames-Per-Second the program will attempt to run at, or -1 if the program
		 * has no Frames-Per-Second limit
		 */
		inline float getTargetFPS( void ) const { return _targetFPS; }

		/*
		 * @param targetFPS: The Frames-Per-Second the program will attempt to run at. Set to -1 to 
		 * remove the Frames-Per-Second limit
		 */
		inline void setTargetFPS( float targetFPS ) { _targetFPS = targetFPS; }

		/*
		 * @returns: The current Frames-Per-Second the program is running at
		 */
		inline float getCurrentFPS( void ) const { return _currentFPS; }

		/* Callback triggered before the update event
		 * 
		 * @param event: The event information, including the FrameData as the data
		 */
		virtual inline void eventUpdateStart( const Event& event ) { }
		
		/* Callback triggered during the update event
		 * 
		 * @param event: The event information, including the FrameData as the data
		 */
        virtual inline void eventUpdate( const Event& event ) { }
		
		/* Callback triggered after the update event
		 * 
		 * @param event: The event information, including the FrameData as the data
		 */
		virtual inline void eventUpdateEnd( const Event& event ) { }
		
		/* Callback triggered before the render event
		 * 
		 * @param event: The event information, including the RenderData as the data
		 */
		virtual inline void eventRenderStart( const Event& event ) { }
		
		/* Callback triggered during the render event
		 * 
		 * @param event: The event information, including the RenderData as the data
		 */
        virtual inline void eventRender( const Event& event ) { }
		
		/* Callback triggered after the render event
		 * 
		 * @param event: The event information, including the RenderData as the data
		 */
		virtual inline void eventRenderEnd( const Event& event ) { }

		inline void eventExit( const Event& event ) { stop(); }

	}; // class GraphicalProgram

} // namespace Arc

#endif // __GRAPHICAL_PROGRAM_H__