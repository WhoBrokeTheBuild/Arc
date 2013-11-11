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
        Texture* _pTexture;

		// The text to render
        string _text;

		// The font to render the text with
        Font* _pFont;

		/* Renders the text using the font onto a new texture, and deletes the old
		 * texture if it exists
		 */
        virtual void renderText( void );

    public:

		/* Creates a rendered text with the specified text and font and then calls 
		 * renderText()
		 * 
		 * @param text: The text to render
		 * @param pFont: A pointer to the font to render the text with
		 */
        RenderedText( const string text, Font* pFont );

		/* Deletes the stored texture if it exists
		 */
        virtual ~RenderedText( void );

        virtual inline string toString( void ) const { return "Rendered Text"; }

		/* Event handler for the graphics reset event. Calls renderText()
		 */
        virtual void graphicsReset( const Event& event );

		/*
		 * @returns: The text to be rendered
		 */
        virtual string getText( void ) const { return _text; }

		/* Sets the text to be rendered and calls renderText()
		 *
		 * @param text: The new text to be rendered
		 */
        virtual void setText( string text );
		
		/*
		 * @returns: The text to be rendered
		 */
        virtual Font* getFont( void ) const { return _pFont; }

		/* Sets the font to render the text with and then calls renderText()
		 *
		 * @param pFont: The new font to render the text with
		 */
        virtual void setFont( Font *pFont);

		/* 
		 * @returns: The size of the texture rendered from the text and font
		 */
        virtual const Size getSize( void ) const;

		/* Get the size of the specified text if it was rendered with the stored font
		 * 
		 * @param text: The text to check the rendered size of
		 * @returns: The size of the text if it was rendered with the stored font
		 */
        virtual Size getStringRenderedSize( string text );

		/* 
		 * @returns: The texture generated with the text and font
		 */
        virtual Texture* getTexture( void ) const { return _pTexture; }

    }; // class CachedText

} // namespace Arc

#endif // __ARC_CACHED_TEXT_H__
