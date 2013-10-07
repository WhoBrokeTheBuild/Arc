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

	/** An image stored in memory
	  */
    class Texture :
        public ManagedObject
    {

        friend class RenderTarget;
        friend class RenderedText;

    private:

		// The filename of the image that was loaded
        string
            _filename;

		// The reference to the texture in OpenGL
        GLuint
            _texture;

		// The width and height of the texture
        Size
            _size;

		// Whether or not the texture was generated or loaded from a file
		bool
			_generated;

        Texture( SDL_Surface* pSurface );

		// Load the texture from a file
        virtual void load( string filename );

		// Load the texture from an SDL_Surface
        virtual void load( SDL_Surface* pSurface );

		// Properly delete the texture from OpenGL's memory
        virtual void deleteTexture( void );

		// Get the OpenGL texture reference 
        virtual GLuint getGLTexture( void ) const { return _texture; }

    public:

        Texture( string filename );
        virtual ~Texture( void );

        virtual inline string toString( void ) const;

		// Handle a graphics reset and reload the texture if it was loaded from a file
        virtual void graphicsReset( const Event& event );

        virtual const Size getSize( void ) const { return _size; }

    }; // class Texture

} // namespace Arc

#endif // __ARC_TEXTURE_H__
