#include "Font.h"
#include "RenderTarget.h"
#include "CachedText.h"

Arc::Font::Font( void )
{
    _filename = string();
    _pFont    = nullptr;
    _size     = 0;
}

void Arc::Font::init( string filename, int size )
{
    _pFont = nullptr;
    _filename = filename;
    _size = size;

    _pFont = TTF_OpenFont(_filename.c_str(), _size);

    if (!_pFont)
    {
        _pFont = nullptr;
        stringstream ss;
        ss << "Cannot load font: " << filename;
        ERROR(toString(), ss.str());
    }
}

void Arc::Font::term( void )
{
    if (_pFont != nullptr)
        TTF_CloseFont(_pFont);
}

std::string Arc::Font::toString( void ) const
{
    stringstream ss;
    ss << "Font [File: " << _filename << ", Size: " << _size << "]";
    return ss.str();
}

Arc::Size Arc::Font::measureString( string text )
{
    int w, h;

    TTF_SizeText(_pFont, text.c_str(), &w, &h);

    return Size((float)w, (float)h);
}