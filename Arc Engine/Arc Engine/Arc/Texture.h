#pragma once

#ifndef __ARC_TEXTURE_H__
#define __ARC_TEXTURE_H__

#include "Common.h"
#include "ManagedObject.h"

#include <SDL/SDL_opengl.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL.h>

namespace Arc
{
    class RenderTarget;
    class RenderedText;
    class Event;

    class Texture :
        public ManagedObject
    {

        friend class RenderTarget;
        friend class RenderedText;

    private:

        string
            _filename;

        GLuint
            _texture;

        Size
            _size;

		bool
			_generated;

        Texture( SDL_Surface* pSurface );

        virtual void load( string filename );
        virtual void load( SDL_Surface* pSurface );

        virtual void deleteTexture( void );

        virtual GLuint getGLTexture( void ) const { return _texture; }

    public:

        Texture( string filename );
        virtual ~Texture( void );

        virtual inline string toString( void ) const;

        virtual void graphicsReset( const Event& event );

        virtual const Size getSize( void ) const { return _size; }

    }; // class Texture

} // namespace Arc

#endif // __ARC_TEXTURE_H__
