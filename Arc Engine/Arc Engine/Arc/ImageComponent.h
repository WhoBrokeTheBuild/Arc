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

		static const ComponentType
			CMP_TYPE_IMAGE;

		ImageComponent( Unit* pUnit,
						Texture* pTexture,
			            Color blendColor = Color::WHITE,
			            Origin origin = Origin::ZERO,
			            Vector2 scale = Vector2::ONE, 
			            Angle rotation = Angle::ZERO,
			            Point offset = Point::ZERO )
			: DrawableComponent(pUnit, blendColor, origin, scale, rotation, offset),
			_pTexture(pTexture)
		{
		}

		virtual inline ~ImageComponent( void ) { }

		virtual inline string toString( void ) const { return "Image Component"; }

		virtual void render( const RenderData* data );

		virtual inline Texture* getTexture( void ) const { return _pTexture; }
		virtual inline void setTexture( Texture* pTexture ) { _pTexture = pTexture; setOriginSize(getSize()); }

		virtual inline Vector2 getSize( void ) const { return (_pTexture == nullptr ? Size::ZERO : _pTexture->getSize()); }

	}; // class ImageComponent

} // namespace Arc

#endif // __ARC_IMAGE_COMPONENT_H__
