#include "RenderedText.h"
#include "GraphicsSystem.h"
#include "RenderTarget.h"
#include "GraphicalProgram.h"

Arc::RenderedText::RenderedText( const string text, Font* pFont )
	: _pTexture(nullptr),
	  _text(text),
      _pFont(pFont)
{
    GraphicalProgram::getGraphicsSystem()->addEventListener(GraphicsSystem::EVENT_GRAPHICS_RESET, this, &RenderedText::graphicsReset);

    renderText();
}

Arc::RenderedText::~RenderedText( void )
{
    GraphicalProgram::getGraphicsSystem()->removeEventListener(GraphicsSystem::EVENT_GRAPHICS_RESET, this, &RenderedText::graphicsReset);

    delete _pTexture;
    _pTexture = nullptr;
}

void Arc::RenderedText::graphicsReset( const Event& event )
{
    renderText();
}

void Arc::RenderedText::renderText( void )
{
    if (_pFont == nullptr || _pFont->getSDLFont() == nullptr)
    {
        ERROR(toString(), "Invalid Font");
        return;
    }

    string text = _text;

    if (text.length() == 0)
        text = " ";

    SDL_Surface* surface = TTF_RenderUTF8_Blended(_pFont->getSDLFont(), text.c_str(), Color::WHITE.getSDLColor());

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

Arc::Size Arc::RenderedText::getStringRenderedSize( string text )
{
    if (_pFont == nullptr || _pFont->getSDLFont() == nullptr)
        return Size::ZERO;

    return _pFont->getStringRenderedSize(text);
}
