#pragma once

#ifndef __ARC_SPRITE_H__
#define __ARC_SPRITE_H__

#include "Common.h"
#include "ManagedObject.h"

#include "Texture.h"

namespace Arc
{
    class Sprite :
        public ManagedObject
    {
    protected:

        Texture
            *_pTexture;
    public:

        Rect
            SourceRect;

        Sprite( void );
        virtual ~Sprite( void ) { term(); }

        virtual inline string toString( void ) const { return "Sprite"; }

        virtual void init( Texture *texture, Rect source );
        virtual void term( void ) { }

        virtual Texture* getTexture( void ) { return _pTexture; }
        virtual void setTexture( Texture* texture ) { _pTexture = texture; }

    }; // class Sprite

} // namespace Arc

#endif // __ARC_SPRITE_H__
