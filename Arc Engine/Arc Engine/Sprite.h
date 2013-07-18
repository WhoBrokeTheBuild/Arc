#pragma once

#ifndef __ARC_SPRITE_H__
#define __ARC_SPRITE_H__

#include "Common.h"
#include "GameObject.h"

#include "Texture.h"

namespace Arc
{
    class Sprite :
        public GameObject
    {
    public:

        Texture
            *pTexture;

        Rect
            SourceRect;

        Sprite( void );
        virtual ~Sprite( void ) { term(); }

        virtual string toString( void ) const;

        virtual void init( Texture *texture, Rect source );
        virtual void term( void );

    };
}

#endif
