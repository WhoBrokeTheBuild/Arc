#pragma once

#ifndef __ARC_TEXT_H__
#define __ARC_TEXT_H__

#include "Common.h"
#include "ManagedObject.h"

#include "Texture.h"
#include "Font.h"
#include "Color.h"

namespace Arc
{
	/** A pre-rendered texture generated from a font and text
	  */
    class RenderedText :
        public ManagedObject
    {
    private:

		// The texture to store the rendered text
        Texture
            *_pTexture;

		// The text to render
        string
            _text;

		// The font to render the text with
        Font
            *_pFont;

		// Render the text to the texture
        virtual void renderText( void );

    public:

        RenderedText( const string text, Font* pFont );
        virtual ~RenderedText( void );

        virtual inline string toString( void ) const { return "Rendered Text"; }

		// Handle a graphics reset and re-render
        virtual void graphicsReset( const Event& event );

        virtual string getText( void ) const { return _text; }
        virtual void setText( string text ); // Set the text and re-render

        virtual Font* getFont( void ) const { return _pFont; }
        virtual void setFont( Font *pFont); // Set the font and re-render

		// Get the size of the rendered texture
        virtual const Size getSize( void ) const;

		// Get the size of the specified text if it was rendered with the stored font
        virtual Size measureString( string text );

        virtual Texture* getTexture( void ) const { return _pTexture; }

    }; // class CachedText

} // namespace Arc

#endif // __ARC_CACHED_TEXT_H__
