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

        Rect
            _sourceRect;

    public:

        Sprite( Texture* pTexture, Rect sourceRect );
        virtual ~Sprite( void );

        virtual inline string toString( void ) const { return "Sprite"; }

        virtual inline Texture* getTexture( void ) { return _pTexture; }
		virtual inline Rect     getSourceRect( void) { return _sourceRect; }

        virtual inline void setTexture( Texture* texture ) { _pTexture = texture; }
        virtual inline void setSourceRect( Rect sourceRect ) { _sourceRect = sourceRect; }

    }; // class Sprite

} // namespace Arc

#endif // __ARC_SPRITE_H__
