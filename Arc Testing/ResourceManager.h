#pragma once

#ifndef __RESOURCE_MANAGER_H__
#define __RESOURCE_MANAGER_H__

#include "Common.h"
#include <Arc/ManagedObject.h>

#include <Arc/Texture.h>
#include <Arc/Sprite.h>
#include <Arc/Animation.h>

class ResourceManager :
	public ManagedObject
{
protected:

	ArrayList<Texture*>
		_textureList;

	ArrayList<Sprite*>
		_spriteList;

	ArrayList<Animation*>
		_animationList;
	
public:

	ResourceManager( void );
	virtual ~ResourceManager( void ) { term(); }

	virtual void init( void );
	virtual void term( void );

	virtual inline string toString( void ) const { return "Resource Manager"; }

	virtual inline unsigned int addTexture  ( Texture* texture )     { _textureList.add(texture);     return _textureList.size()   - 1; }
	virtual inline unsigned int addSprite   ( Sprite* sprite)        { _spriteList.add(sprite);       return _spriteList.size()    - 1; }
	virtual inline unsigned int addAnimation( Animation* animation ) { _animationList.add(animation); return _animationList.size() - 1; } 
	
	virtual inline Texture*   getTexture  ( unsigned int index ) { return _textureList[index]; }
	virtual inline Sprite*    getSprite   ( unsigned int index ) { return _spriteList[index]; }
	virtual inline Animation* getAnimation( unsigned int index ) { return _animationList[index]; }

};

#endif // __RESOURCE_MANAGER_H__