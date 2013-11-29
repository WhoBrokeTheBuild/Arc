#pragma once

#ifndef __ARC_GRAPHICS_SYSTEM_H__
#define __ARC_GRAPHICS_SYSTEM_H__

#include "Common.h"
#include "SystemComponent.h"

#include "RenderTarget.h"
#include "Color.h"

#include <SDL/SDL.h>
#include <SDL/SDL_opengl.h>
#include <SDL/SDL_ttf.h>

namespace Arc
{
	/** A system for managing the window and drawing.
	  */
    class GraphicsSystem :
        public SystemComponent
    {
    private:

		// Color to clear the background to at the beginning of every render
        Color _clearColor; 

		// The render target, used for drawing primitives and textures
        RenderTarget* _pRenderTarget; 

		// The bytes-per-pixel of the screen
        int _screenBPP; 

		// The size of the window
        Size _windowSize; 

		// The title of the window
        string _windowTitle;

		// Whether or not the window is fullscreen
        bool _fullscreen;

		/* Reset OpenGL and reload all texture and font data
		 */
        void resetGL( void );
		
		/* Reset SDL and reload OpenGL
		 */
        void resetVideoMode( void );

    public:

		static const SystemComponentType SYS_CMP_TYPE_GRAPHICS;

		// The event called when the graphics context is changed
        static const EventType EVENT_GRAPHICS_RESET;

		/* Creates a graphics system and window with the specified parameters
		 * 
		 * @param windowSize: The size of the window to be created
		 * @param windowTitle: The text to show at the top of the window
		 * @param clearColor: The color to clear the window to at the start of every frame
		 *		default: Color::BLACK
		 */
        GraphicsSystem( Program* pProgram, Size windowSize, string windowTitle, Color clearColor, bool fullscreen );

		/* Cleans up the underlying systems and closes the graphics system
		 */
        virtual ~GraphicsSystem( void );

        virtual inline string toString( void ) const { return "Graphics System"; }

		/* 
		 * @param fullscreen: Whether the window should be fullscreen or not
		 */
        virtual void setFullscreen ( bool fullscreen );

		/* 
		 * @param size: The size the window should be, should have a positive width and height
		 */
        virtual void setWindowSize ( Size size );

		/* 
		 * @param title: The title that the window should have
		 */
        virtual void setWindowTitle( string title );

		/* 
		 * @param clearColor: The color to clear the window to every frame
		 */
		virtual inline void setClearColor ( Color clearColor ) { _clearColor = clearColor; }

		/* 
		 * @returns: Whether or not the window is fullscreen
		 */
        virtual inline bool   isFullscreen  ( void ) { return _fullscreen;  }

		/* 
		 * @returns: The current size of the window
		 */
        virtual inline Size   getWindowSize ( void ) { return _windowSize;  }

		/* 
		 * @returns: The current title of the window
		 */
        virtual inline string getWindowTitle( void ) { return _windowTitle; }

		/* 
		 * @returns: The current clear color
		 */
        virtual inline Color  getClearColor ( void ) { return _clearColor;  }

		/* Loads an image and sets it as the window icon
		 * 
		 * @param filename: The filename of the image to load
		 */
		virtual void setWindowIcon ( string filename );

		/* 
		 * @returns: The render target 
		 */
        virtual RenderTarget *getRenderTarget( void ) { return _pRenderTarget; };

    }; // class GraphicsSystem

} // namespace Arc

#endif // __ARC_GRAPHICS_SYSTEM_H__
