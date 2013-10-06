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

		ImageComponent( Unit* pUnit, 
						Texture *pTexture,
						Point offset = Point::ZERO,
						Point origin = Point::ZERO,
						Vector2 scale = Vector2::ONE,
						Angle rotation = Angle::ZERO, 
						Color blendColor = Color::WHITE );
		ImageComponent( Unit* pUnit,
						Texture *pTexture,
						Point offset = Point::ZERO,
						OriginLocation originLocation = OriginLocation::ORIGIN_LOCATION_TOP_LEFT,
						Vector2 scale = Vector2::ONE,
						Angle rotation = Angle::ZERO,
						Color blendColor = Color::WHITE );
		virtual inline ~ImageComponent( void );

		virtual inline string toString( void ) const { return "Image Component"; }

		virtual void render( const RenderData* data );

		virtual inline Texture* getTexture( void ) const { return _pTexture; }
		virtual inline void setTexture( Texture* pTexture ) { _pTexture = pTexture; }

		virtual inline Vector2 getSize( void ) const { return (_pTexture == nullptr ? Size::ZERO : _pTexture->getSize()); }

	}; // class ImageComponent

} // namespace Arc

#endif // __ARC_IMAGE_COMPONENT_H__
