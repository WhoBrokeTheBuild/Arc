#include "Texture.h"
#include "RenderTarget.h"
#include "RenderedText.h"
#include "GraphicsSystem.h"
#include "Event.h"
#include "GraphicalProgram.h"

Arc::Texture::Texture( string filename )
{
    load(filename);

	// Only attach the EVENT_GRAPHICS_RESET event if the texture was loaded from file
    GraphicalProgram::getGraphicsSystem()->addEventListener(GraphicsSystem::EVENT_GRAPHICS_RESET, this, &Texture::graphicsReset);
}

Arc::Texture::Texture( SDL_Surface* pSurface )
{
    load(pSurface);
	_generated;
}

Arc::Texture::~Texture( void )
{
	// Only remove the EVENT_GRAPHICS_RESET event if the texture was loaded from file
	if ( ! _generated)
		GraphicalProgram::getGraphicsSystem()->removeEventListener(GraphicsSystem::EVENT_GRAPHICS_RESET, this, &Texture::graphicsReset);
    deleteTexture();
}

std::string Arc::Texture::toString( void ) const
{
    stringstream ss;
    ss << "Texture [File: " << _filename << "]";
    return ss.str();
}

void Arc::Texture::load( string filename )
{
    _filename = filename;

	// Load the texture from a file
    SDL_Surface *surface = IMG_Load(_filename.c_str());

    if ( ! surface)
        ERRORF(toString(), "Error Loading Image (%s)", IMG_GetError());

    load(surface);

    SDL_FreeSurface(surface);
}

void Arc::Texture::load( SDL_Surface* pSurface )
{
	// Delete the previous texture if it exists
    deleteTexture();

	// Generate a new texture in OpenGL
    glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
    _texture = OPENGL_INVALID_TEXTURE;
    glGenTextures(1, &_texture);
    glBindTexture(GL_TEXTURE_2D, _texture);

    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

    _size = Size((float)pSurface->w, (float)pSurface->h);

    GLenum mode = GL_RGB;

    if (pSurface->format->BytesPerPixel == 4)
    {
        mode = GL_RGBA;
    }

	// Load the texture into OpenGL from the SDL_Surface
    glTexImage2D(GL_TEXTURE_2D, 0, 4, (int)_size.getWidth(), (int)_size.getHeight(), 0, mode, GL_UNSIGNED_BYTE, pSurface->pixels);

	// Set OpenGL Filters to prevent blurring
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,      GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,      GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,  GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,  GL_LINEAR);
}

void Arc::Texture::graphicsReset( const Event& event )
{
    if ( ! _generated)
    {
        deleteTexture();
        load(_filename);
    }
}

void Arc::Texture::deleteTexture( void )
{
    if (_texture != OPENGL_INVALID_TEXTURE)
        glDeleteTextures(1, &_texture);
}
