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

void Sprite::init( Texture *texture, Rect source, double frameTime /*= 0 */ )
{
    SourceRect = source;
    pTexture = texture;
    FrameTime = frameTime;
}

void Sprite::term( void )
{
}
