#include "ResourceManager.h"

ResourceManager::ResourceManager(void)
{
}

void ResourceManager::init( void )
{
	_textureList   = ArrayList<Texture*>();
	_spriteList    = ArrayList<Sprite*>();
	_animationList = ArrayList<Animation*>();
}

void ResourceManager::term( void )
{
	while ( ! _textureList.empty())
		delete _textureList.popBack();

	while ( ! _spriteList.empty())
		delete _spriteList.popBack();

	while ( ! _animationList.empty())
		delete _animationList.popBack();
}
