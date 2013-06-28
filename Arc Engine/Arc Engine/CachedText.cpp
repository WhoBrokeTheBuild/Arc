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
    if (_pFont == nullptr || _pFont->SDLFont() == nullptr)
    {
        ERR(toString(), "Invalid Font");
        return;
    }

    string text = _text;

    if (text.length() == 0)
        text = " ";

    SDL_Surface* surface = TTF_RenderUTF8_Blended(_pFont->SDLFont(), text.c_str(), Color::WHITE.SDLColor());

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
    if (_pTexture == nullptr)
        return Size::ZERO;

    return _pTexture->size();
}

Size CachedText::measureString( string text )
{
    if (_pFont == nullptr || _pFont->SDLFont() == nullptr)
        return Size::ZERO;

    return _pFont->measureString(text);
}
