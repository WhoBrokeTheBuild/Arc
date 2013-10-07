#pragma once

#ifndef __ARC_GRAPHICS_SYSTEM_H__
#define __ARC_GRAPHICS_SYSTEM_H__

#include "Common.h"
#include "EventDispatcher.h"

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
        public EventDispatcher
    {
    private:

		// Color to clear the background to
        Color
            _clearColor; 

		// The render target, used for drawing primitives and textures
        RenderTarget
            *_pRenderTarget; 

		// The bytes-per-pixel of the screen
        int
            _screenBPP; 

		// The size of the window
        Size
            _windowSize; 

		// The title of the window
        string
            _windowTitle;

		// Whether or not the window is fullscreen
        bool
            _fullscreen;

		// Reset OpenGL and reload all texture and font data
        void resetGL( void );

		// Reset SDL and reload OpenGL
        void resetVideoMode( void );

    public:

        static const EventType 
			EVENT_GRAPHICS_RESET;

        GraphicsSystem( Size windowSize, string windowTitle, Color clearColor );
        virtual ~GraphicsSystem( void );

        virtual inline string toString( void ) const { return "Graphics System"; }

        virtual void setFullscreen ( bool fullscreen );
        virtual void setWindowSize ( Size size );
        virtual void setWindowTitle( string title );
		virtual inline void setClearColor ( Color clearColor ) { _clearColor = clearColor; }

        virtual inline bool   isFullscreen  ( void ) { return _fullscreen;  }
        virtual inline Size   getWindowSize ( void ) { return _windowSize;  }
        virtual inline string getWindowTitle( void ) { return _windowTitle; }
        virtual inline Color  getClearColor ( void ) { return _clearColor;  }

		// Load an image and set it as the icon of the window
		virtual void setWindowIcon ( string filename );

        virtual RenderTarget *getRenderTarget( void ) { return _pRenderTarget; };

    }; // class GraphicsSystem

} // namespace Arc

#endif // __ARC_GRAPHICS_SYSTEM_H__
