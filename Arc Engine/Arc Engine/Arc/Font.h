#pragma once

#ifndef __ARC_FONT_H__
#define __ARC_FONT_H__

#include "Common.h"
#include "ManagedObject.h"

#include <SDL/SDL_ttf.h>

namespace Arc
{
    class RenderTarget;
    class RenderedText;

	/** A TTF font with a font size.
	  */
    class Font :
        public ManagedObject
    {

        friend class RenderTarget;
        friend class RenderedText;

    private:

		// Filename of the font, used during a graphics reset
        string
            _filename; 

		// SDL TTF_Font struct
        TTF_Font
            *_pFont; 

		// Size of the text 
        int
            _fontSize; 

		// Get the SDL TTF_Font struct
        virtual TTF_Font* SDLFont( void ) const { return _pFont; }

    public:

        Font( string filename, int size );
        virtual ~Font( void );

        virtual inline string toString( void ) const;

        virtual int getFontSize( void ) const { return _fontSize; }

		// Get the width and height of the texture if the text was rendered using the font and size
        virtual Size measureString( string text );

    }; // class Font

} // namespace Arc

#endif // __ARC_FONT_H__
