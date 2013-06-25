#include "CachedText.h"
#include "GraphicsSystem.h"
#include "RenderTarget.h"

CachedText::CachedText( void )
{
    _pTexture = nullptr;
    _pFont = nullptr;
    _text = string();
}

CachedText::~CachedText( void )
{
    term();
}

std::string CachedText::toString( void ) const
{
    return "Text";
}

void CachedText::init( string text, Font* pFont )
{
    _pFont = pFont;
    _text = text;
    renderText();

    gpEventDispatcher->addEventListener(GraphicsSystem::EVENT_GRAPHICS_RESET, this, &CachedText::graphicsReset);
}

void CachedText::term( void )
{
    gpEventDispatcher->removeEventListener(GraphicsSystem::EVENT_GRAPHICS_RESET, this, &CachedText::graphicsReset);

    delete _pTexture;
    _pTexture = nullptr;
}

void CachedText::graphicsReset( const Event& event )
{
    renderText();
}

void CachedText::renderText( void )
{
    if (_pFont->SDLFont() == nullptr)
    {
        ERR(toString(), "Invalid Font");
        return;
    }

    if (_text.length() == 0)
        return;

    SDL_Surface *surface = TTF_RenderUTF8_Blended(_pFont->SDLFont(), _text.c_str(), Color::WHITE.SDLColor());

    if (!surface)
    {
        ERR(toString(), "Invalid Surface");
        return;
    }

    delete _pTexture;
    _pTexture = nullptr;

    _pTexture = New Texture();
    _pTexture->init(surface);

    SDL_FreeSurface(surface);
}

void CachedText::setText( string text )
{
    _text = text;
    renderText();
}

Size CachedText::size( void )
{
    return _pTexture->size();
}
