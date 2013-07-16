#include "Font.h"
#include "RenderTarget.h"
#include "CachedText.h"

Font::Font( string filename, int size )
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

Font::~Font( void )
{
    if (_pFont != nullptr)
        TTF_CloseFont(_pFont);
}

string Font::toString( void ) const
{
    return "Font";
}

Size Font::measureString( string text )
{
    int w, h;

    TTF_SizeText(_pFont, text.c_str(), &w, &h);

    return Size((float)w, (float)h);
}
