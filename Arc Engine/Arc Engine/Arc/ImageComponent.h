#pragma once

#ifndef __ARC_IMAGE_COMPONENT_H__
#define __ARC_IMAGE_COMPONENT_H__

#include "Common.h"
#include "Component.h"

#include "Texture.h"

namespace Arc
{
	class ImageComponent :
		public Component
	{
	protected:

		Texture
			*_pTexture;

	public:

		Point
			Offset,
			Origin;

		Angle
			Rotation;

		Color
			BlendColor;

		ImageComponent( void );
		virtual inline ~ImageComponent( void ) { term (); }

		virtual void init( Texture *pTexture, Point offset = Point::ZERO, Angle rotation = Angle::ZERO, Color blendColor = Color::WHITE, Point origin = Point::ZERO );
		virtual void term( void );

		virtual inline string toString( void ) const { return "Image Component"; }

		virtual void render( const RenderData* data );

		virtual inline Texture* getTexture( void ) const { return _pTexture; }
		virtual inline void setTexture( Texture* pTexture ) { _pTexture = pTexture; }

	}; // class ImageComponent

} // namespace Arc

#endif // __ARC_IMAGE_COMPONENT_H__
