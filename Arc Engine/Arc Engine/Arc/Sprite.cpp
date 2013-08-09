#include "Sprite.h"

Arc::Sprite::Sprite( void )
{
    _pTexture  = nullptr;
    SourceRect = Rect::ZERO;
}

void Arc::Sprite::init( Texture *texture, Rect source )
{
    SourceRect = source;
    _pTexture  = texture;
}
