#pragma once

#ifndef __ARC_IMAGE_COMPONENT_H__
#define __ARC_IMAGE_COMPONENT_H__

#include "Common.h"
#include "DrawableComponent.h"

#include "Texture.h"

namespace Arc
{
	class ImageComponent :
		public DrawableComponent
	{
	protected:

		Texture
			*_pTexture;

	public:

		ImageComponent( Unit* pUnit, Texture *pTexture, Point offset = Point::ZERO, Angle rotation = Angle::ZERO, Color blendColor = Color::WHITE, Point origin = Point::ZERO );
		virtual inline ~ImageComponent( void );

		virtual inline string toString( void ) const { return "Image Component"; }

		virtual void render( const RenderData* data );

		virtual inline Texture* getTexture( void ) const { return _pTexture; }
		virtual inline void setTexture( Texture* pTexture ) { _pTexture = pTexture; }

	}; // class ImageComponent

} // namespace Arc

#endif // __ARC_IMAGE_COMPONENT_H__
