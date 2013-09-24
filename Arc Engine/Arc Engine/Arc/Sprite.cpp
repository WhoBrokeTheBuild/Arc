#include "Sprite.h"

Arc::Sprite::Sprite( Texture* pTexture, Rect sourceRect )
	: _pTexture(pTexture),
	  _sourceRect(sourceRect)
{
}

Arc::Sprite::~Sprite( void )
{
}
