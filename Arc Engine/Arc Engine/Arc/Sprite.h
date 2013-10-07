#pragma once

#ifndef __ARC_SPRITE_H__
#define __ARC_SPRITE_H__

#include "Common.h"
#include "ManagedObject.h"

#include "Texture.h"

namespace Arc
{
	/** A texture and the source rect of the image on the texture
	  */
    class Sprite :
        public ManagedObject
    {
    protected:

		// The texture to take a spot from
        Texture
            *_pTexture;

		// The source rectangle of the spot to take
        Rect
            _sourceRect;

    public:

		inline Sprite( Texture* pTexture, Rect sourceRect )
			: _pTexture(pTexture),
			_sourceRect(sourceRect)
		{
		}

        virtual inline ~Sprite( void )
		{
		}

        virtual inline string toString( void ) const { return "Sprite"; }

        virtual inline Texture* getTexture( void ) { return _pTexture; }
		virtual inline Rect     getSourceRect( void) { return _sourceRect; }

        virtual inline void setTexture( Texture* texture ) { _pTexture = texture; }
        virtual inline void setSourceRect( Rect sourceRect ) { _sourceRect = sourceRect; }

    }; // class Sprite

} // namespace Arc

#endif // __ARC_SPRITE_H__
