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
        string _filename;

		// The reference to the texture in OpenGL
        GLuint _texture;

		// The width and height of the texture
        Size _size;

		// Whether or not the texture was generated or loaded from a file
		bool _generated;
		
		/* Creates a texture from an SDL_Surface and loads it into OpenGL
		 *
		 * @param pSurface: A pointer to the SDL_Surface to load into OpenGL 
		 */
        Texture( SDL_Surface* pSurface );

		/* Load a texture from a file and deletes the old one if it exists by calling
		 * deleteTexture()
		 * 
		 * @param filename: The filename of the image to load
		 */
        virtual void load( string filename );
		
		/* Load a texture from a SDL_Surface and loads it into OpenGL and deletes the 
		 * old one if it exists deleteTexture()
		 * 
		 * @param pSurface: The SDL_Surface to load into OpenGL
		 */
        virtual void load( SDL_Surface* pSurface );

		/* Properly delete the texture from OpenGL's memory
		 */
        virtual void deleteTexture( void );
		
		/* 
		 * @returns: Get the OpenGL Texture reference
		 */
        virtual GLuint getGLTexture( void ) const { return _texture; }

    public:
		
		/* Loads an image from a file and creates a new texture from it
		 * 
		 * @param filename: The filename of the image to load
		 */
        Texture( string filename );

		/* Cleans up the texture from OpenGL by calling deleteTexture();
		 */
        virtual ~Texture( void );

        virtual inline string toString( void ) const;

		/* Event handler for the graphics reset event. Reloads the texture if it was loaded from a file
		 * 
		 */
        virtual void graphicsReset( const Event& event );

		/*
		 * @returns: The width and height of the texture
		 */
        virtual const Size getSize( void ) const { return _size; }

    }; // class Texture

} // namespace Arc

#endif // __ARC_TEXTURE_H__
