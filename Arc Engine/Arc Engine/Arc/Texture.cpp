#include "Texture.h"
#include "RenderTarget.h"
#include "CachedText.h"
#include "GraphicsSystem.h"
#include "Event.h"

Arc::Texture::Texture( void )
{
    _size = Size::ZERO;
    _filename = string();
}

std::string Arc::Texture::toString( void ) const
{
    stringstream ss;
    ss << "Texture [File: " << _filename << "]";
    return ss.str();
}

void Arc::Texture::init( string filename )
{
    load(filename);
    gpEventDispatcher->addEventListener(GraphicsSystem::EVENT_GRAPHICS_RESET, this, &Texture::graphicsReset);
}

void Arc::Texture::init( SDL_Surface* pSurface )
{
    load(pSurface);
}

void Arc::Texture::term( void )
{
    gpEventDispatcher->removeEventListener(GraphicsSystem::EVENT_GRAPHICS_RESET, this, &Texture::graphicsReset);

    deleteTexture();
}

void Arc::Texture::load( string filename )
{
    _filename = filename;

    SDL_Surface *surface = IMG_Load(_filename.c_str());

    if (!surface)
        ERRORF(toString(), "Error Loading Image (%s)", IMG_GetError());

    load(surface);

    SDL_FreeSurface(surface);
}

void Arc::Texture::load( SDL_Surface* pSurface )
{
    if (_filename == "")
        _filename = "<generated>";

    if (_texture != OPENGL_INVALID_TEXTURE)
        glDeleteTextures(1, &_texture);

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

    glTexImage2D(GL_TEXTURE_2D, 0, 4, (int)_size.width(), (int)_size.height(), 0, mode, GL_UNSIGNED_BYTE, pSurface->pixels);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,      GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,      GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,  GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,  GL_LINEAR);
}

void Arc::Texture::graphicsReset( const Event& event )
{
    if (_filename != "" && _filename[0] != '<') // Prevent <generated>
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
