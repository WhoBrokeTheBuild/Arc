#pragma once

#ifndef __ARC_TEXT_H__
#define __ARC_TEXT_H__

#include "Common.h"
#include "GameObject.h"

#include "Texture.h"
#include "Font.h"
#include "Color.h"

namespace Arc
{
    class CachedText :
        public GameObject
    {
    private:

        Texture
            *_pTexture;

        string
            _text;

        Font
            *_pFont;

    public:

        CachedText( void );
        virtual ~CachedText( void ) { term(); }

        virtual string toString( void ) const { return "Cached Text"; }

        virtual void init( const string text, Font* pFont );
        virtual void term( void );

        virtual void graphicsReset( const Event& event );
        virtual void renderText( void );

        virtual string getText( void ) const { return _text; }
        virtual void setText( string text );

        virtual const Size size( void ) const;
        virtual Size measureString( string text );

        virtual Texture* getTexture( void ) const { return _pTexture; }

    }; // class CachedText

} // namespace Arc

#endif // __ARC_CACHED_TEXT_H__
