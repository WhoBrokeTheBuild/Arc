#pragma once

#ifndef __SPRITE_H__
#define __SPRITE_H__

#include "ArcCommon.h"
#include "GameObject.h"

#include "Texture.h"

class Sprite :
    public GameObject
{
public:

    Texture
        *pTexture;

    Rect
        SourceRect;

    Sprite( void );
    virtual ~Sprite( void );

    virtual string toString( void ) const;

    virtual void init( Texture *texture, Rect source );
    virtual void term( void );

};

#endif
