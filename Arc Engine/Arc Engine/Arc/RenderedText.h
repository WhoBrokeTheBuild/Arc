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
    class RenderedText :
        public ManagedObject
    {
    private:

        Texture
            *_pTexture;

        string
            _text;

        Font
            *_pFont;

		Color 
			_color;

        virtual void renderText( void );

    public:

        RenderedText( const string text, Font* pFont, Color color = Color::WHITE );
        virtual ~RenderedText( void );

        virtual inline string toString( void ) const { return "Rendered Text"; }

        virtual void graphicsReset( const Event& event );

        virtual string getText( void ) const { return _text; }
        virtual void setText( string text );

        virtual const Size getSize( void ) const;
        virtual Size measureString( string text );

        virtual Texture* getTexture( void ) const { return _pTexture; }

    }; // class CachedText

} // namespace Arc

#endif // __ARC_CACHED_TEXT_H__
