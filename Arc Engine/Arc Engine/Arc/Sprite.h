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
    protected:

        Texture
            *pTexture;
    public:

        Rect
            SourceRect;

        Sprite( void );
        virtual ~Sprite( void ) { term(); }

        virtual string toString( void ) const { return "Sprite"; }

        virtual void init( Texture *texture, Rect source );
        virtual void term( void ) { }

        virtual Texture* getTexture( void ) { return pTexture; }
        virtual void setTexture( Texture* texture ) { pTexture = texture; }

    }; // class Sprite

} // namespace Arc

#endif // __ARC_SPRITE_H__
