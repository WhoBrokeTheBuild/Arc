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

		// Filename of the font, used to reload the font during a graphics reset
        string _filename; 

		// SDL TTF_Font struct to hold the actual font, starts off null
        TTF_Font* _pFont; 

		// Size of the text drawn with the font
        int _fontSize; 

		/* 
		 * @returns: The SDL TTF_Font struct
		 */
        virtual inline TTF_Font* getSDLFont( void ) const { return _pFont; }

    public:

		/* Loads the specified font file with the size given, _pFont will be null on error
		 *
		 * @param filename: The path to the font file to load
		 * @param size: The size of text to be drawn with the font
		 */
        Font( string filename, int size );

        virtual ~Font( void );

        virtual inline string toString( void ) const;

		/*
		 * @returns: Whether or not the font has been loaded
		 */
		virtual inline bool isLoaded( void ) const { return _pFont == nullptr; }
		
		/* 
		 * @returns: The font size
		 */
        virtual inline int getFontSize( void ) const { return _fontSize; }

		/* Get the width and height of the texture if the text was rendered using the font and size
		 *
		 * @returns: The size of the texture if the font is loaded or a size with a width and height of 0
		 */ 
        virtual Size measureString( string text );

    }; // class Font

} // namespace Arc

#endif // __ARC_FONT_H__
