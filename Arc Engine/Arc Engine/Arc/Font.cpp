#include "Font.h"
#include "RenderTarget.h"
#include "RenderedText.h"

Arc::Font::Font( string filename, int size )
	: _pFont(nullptr),
	  _filename(filename),
	  _fontSize(size)
{
    _pFont = TTF_OpenFont(_filename.c_str(), _fontSize);

    if ( ! _pFont)
    {
        _pFont = nullptr;
        stringstream ss;
        ss << "Cannot load font: " << filename;
        ERROR(toString(), ss.str());
    }
}

Arc::Font::~Font( void )
{
    if (_pFont != nullptr)
        TTF_CloseFont(_pFont);
}

std::string Arc::Font::toString( void ) const
{
    stringstream ss;
    ss << "Font [File: " << _filename << ", Size: " << _fontSize << "]";
    return ss.str();
}

Arc::Size Arc::Font::measureString( string text )
{
    int w, h;

    TTF_SizeText(_pFont, text.c_str(), &w, &h);

    return Size((float)w, (float)h);
}