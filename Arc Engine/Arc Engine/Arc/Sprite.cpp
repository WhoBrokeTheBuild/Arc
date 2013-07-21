#include "Sprite.h"

Arc::Sprite::Sprite( void )
{
    pTexture   = nullptr;
    SourceRect = Rect::ZERO;
}

void Arc::Sprite::init( Texture *texture, Rect source )
{
    SourceRect = source;
    pTexture = texture;
}
