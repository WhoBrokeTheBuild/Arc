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
    class GraphicsSystem :
        public EventDispatcher
    {
    private:

        Color
            _clearColor;

        RenderTarget
            *_pRenderTarget;

        int
            _screenBPP;

        Size
            _windowSize;

        string
            _windowTitle;

        bool
            _fullscreen;

        void resetGL( void );
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
        virtual void setWindowIcon ( string filename );
		virtual inline void setClearColor ( Color clearColor ) { _clearColor = clearColor; }

        virtual bool   isFullscreen  ( void ) { return _fullscreen;  }
        virtual Size   getWindowSize ( void ) { return _windowSize;  }
        virtual string getWindowTitle( void ) { return _windowTitle; }
        virtual Color  getClearColor ( void ) { return _clearColor;  }

        virtual RenderTarget *getRenderTarget( void ) { return _pRenderTarget; };

    }; // class GraphicsSystem

} // namespace Arc

#endif // __ARC_GRAPHICS_SYSTEM_H__
