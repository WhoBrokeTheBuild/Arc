#include "Sprite.h"

Sprite::Sprite( void )
{
    pTexture = nullptr;
}

Sprite::~Sprite( void )
{
    term();
}

string Sprite::toString( void ) const
{
    return "Sprite";
}

void Sprite::init( Texture *texture, Rect source )
{
    SourceRect = source;
    pTexture = texture;
}

void Sprite::term( void )
{
}
