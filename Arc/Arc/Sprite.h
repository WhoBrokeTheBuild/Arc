#pragma once

#ifndef __ARC_SPRITE_H__
#define __ARC_SPRITE_H__

#include "Common.h"
#include "ManagedObject.h"

#include "Texture.h"

namespace Arc
{
	/** A texture and the source rectangle of the image on the texture
	  */
    class Sprite :
        public ManagedObject
    {
    protected:

		// The texture to take a spot from
        Texture* _pTexture;

		// The source rectangle of the spot to take
        Rect _sourceRect;

    public:

		/* Creates a new sprite with the specified texture and source rect
		 * 
		 * @param pTexture: A pointer to the texture
		 * @param sourceRect: The source rectangle 
		 */
		inline Sprite( Texture* pTexture, Rect sourceRect )
			: _pTexture(pTexture),
			_sourceRect(sourceRect)
		{
		}

        virtual inline ~Sprite( void ) { }

        virtual inline string toString( void ) const { return "Sprite"; }

		/* 
		 * @returns: A pointer to the texture
		 */
        virtual inline Texture* getTexture( void ) { return _pTexture; }
		
		/* 
		 * @returns: The source rectangle 
		 */
		virtual inline Rect getSourceRect( void) { return _sourceRect; }
		
		/* 
		 * @param pTexture: A pointer to the new texture
		 */
        virtual inline void setTexture( Texture* pTexture ) { _pTexture = pTexture; }
		
		/* 
		 * @param sourceRect: The new source rectangle
		 */
        virtual inline void setSourceRect( Rect sourceRect ) { _sourceRect = sourceRect; }

    }; // class Sprite

} // namespace Arc

#endif // __ARC_SPRITE_H__
