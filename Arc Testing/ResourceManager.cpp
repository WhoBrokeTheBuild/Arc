#include "ResourceManager.h"

ResourceManager::ResourceManager( void )
	: _textureList(),
	  _spriteList(),
	  _animationList(),
	  _soundList()
{
}

ResourceManager::~ResourceManager( void )
{
	while ( ! _textureList.isEmpty())
		delete _textureList.popBack();

	while ( ! _spriteList.isEmpty())
		delete _spriteList.popBack();

	while ( ! _animationList.isEmpty())
		delete _animationList.popBack();

	while ( ! _soundList.isEmpty())
		delete _soundList.popBack();
}
