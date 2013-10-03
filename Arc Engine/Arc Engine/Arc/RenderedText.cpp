#include "RenderedText.h"
#include "GraphicsSystem.h"
#include "RenderTarget.h"

Arc::RenderedText::RenderedText( const string text, Font* pFont )
	: _pTexture(nullptr),
	  _text(text),
      _pFont(pFont)
{
    gpEventDispatcher->addEventListener(GraphicsSystem::EVENT_GRAPHICS_RESET, this, &RenderedText::graphicsReset);

    renderText();
}

Arc::RenderedText::~RenderedText( void )
{
    gpEventDispatcher->removeEventListener(GraphicsSystem::EVENT_GRAPHICS_RESET, this, &RenderedText::graphicsReset);

    delete _pTexture;
    _pTexture = nullptr;
}

void Arc::RenderedText::graphicsReset( const Event& event )
{
    renderText();
}

void Arc::RenderedText::renderText( void )
{
    if (_pFont == nullptr || _pFont->SDLFont() == nullptr)
    {
        ERROR(toString(), "Invalid Font");
        return;
    }

    string text = _text;

    if (text.length() == 0)
        text = " ";

    SDL_Surface* surface = TTF_RenderUTF8_Blended(_pFont->SDLFont(), text.c_str(), Color::WHITE.getSDLColor());

    if ( ! surface)
    {
        ERROR(toString(), "Invalid Surface");
        return;
    }

    delete _pTexture;
    _pTexture = New Texture(surface);

    SDL_FreeSurface(surface);
}

void Arc::RenderedText::setText( string text )
{
    _text = text;
    renderText();
}

void Arc::RenderedText::setFont( Font *pFont )
{
    _pFont = pFont;
    renderText();
}

const Arc::Size Arc::RenderedText::getSize( void ) const
{
    if (_pTexture == nullptr)
        return Size::ZERO;

    return _pTexture->getSize();
}

Arc::Size Arc::RenderedText::measureString( string text )
{
    if (_pFont == nullptr || _pFont->SDLFont() == nullptr)
        return Size::ZERO;

    return _pFont->measureString(text);
}
