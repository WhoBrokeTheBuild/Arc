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

    class Font :
        public ManagedObject
    {

        friend class RenderTarget;
        friend class RenderedText;

    private:

        string
            _filename;

        TTF_Font
            *_pFont;

        int
            _fontSize;

        virtual TTF_Font* SDLFont( void ) const { return _pFont; }

    public:

        Font( string filename, int size );
        virtual ~Font( void );

        virtual inline string toString( void ) const;

        virtual int getFontSize( void ) const { return _fontSize; }

        virtual Size measureString( string text );

    }; // class Font

} // namespace Arc

#endif // __ARC_FONT_H__
