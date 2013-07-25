#pragma once

#ifndef __ARC_TEXTURE_H__
#define __ARC_TEXTURE_H__

#include "Common.h"
#include "GameObject.h"

#include <SDL/SDL_opengl.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL.h>

namespace Arc
{
    class RenderTarget;
    class CachedText;
    class Event;

    class Texture :
        public GameObject
    {

        friend class RenderTarget;
        friend class CachedText;

    private:

        string
            _filename;

        GLuint
            _texture;

        Size
            _size;

        virtual void init( SDL_Surface* pSurface );

        virtual void load( string filename );
        virtual void load( SDL_Surface* pSurface );

        virtual void deleteTexture( void );

        virtual GLuint getGLTexture( void ) const { return _texture; }

    public:

        Texture( void );
        virtual ~Texture( void ) { term(); }

        virtual string toString( void ) const;

        virtual void init( string filename );
        virtual void term( void );

        virtual void graphicsReset( const Event& event );

        virtual const Size size( void ) const { return _size; }

    }; // class Texture

} // namespace Arc

#endif // __ARC_TEXTURE_H__
