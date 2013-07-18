#include "Sprite.h"

Arc::Sprite::Sprite( void )
{
    pTexture = nullptr;
}

Arc::string Sprite::toString( void ) const
{
    return "Sprite";
}

void Arc::Sprite::init( Texture *texture, Rect source )
{
    SourceRect = source;
    pTexture = texture;
}

void Arc::Sprite::term( void )
{
}
