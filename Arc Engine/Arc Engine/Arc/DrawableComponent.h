#pragma once

#ifndef __ARC_DRAWABLE_COMPONENT_H__
#define __ARC_DRAWABLE_COMPONENT_H__

#include "Common.h"
#include "Component.h"

#include "OriginLocation.h"
#include "Origin.h"

namespace Arc
{
	class DrawableComponent :
		public Component
	{
	protected:

		OriginLocation
			_originLocation;

		Point
			_offset;

		Origin 
			_origin;

		Vector2
			_scale;

		Angle
			_rotation;

		Color
			_blendColor;

		virtual inline void setOriginSize( Size size ) { _origin.setSize(size); }

	public:

		static const ComponentType
			CMP_TYPE_DRAWABLE;

		inline DrawableComponent( Unit* pUnit,
			               Color blendColor = Color::WHITE,
			               Origin origin = Origin::ZERO,
			               Vector2 scale = Vector2::ONE, 
			               Angle rotation = Angle::ZERO,
			               Point offset = Point::ZERO )
			: Component(pUnit),
			  _blendColor(blendColor),
			  _origin(origin),
			  _scale(scale),
			  _rotation(rotation),
			  _offset(offset)
		{
		}

		virtual inline ~DrawableComponent( void ) { }

		virtual inline string toString( void ) const { return "Drawable Component"; }

		virtual inline Point   getOffset    ( void ) const { return _offset; }
		virtual inline Vector2 getScale     ( void ) const { return _scale; }
		virtual inline Angle   getRotation  ( void ) const { return _rotation; }
		virtual inline Color   getBlendColor( void ) const { return _blendColor; }
		
		virtual inline void setOffset    ( Point offset )     { _offset = offset; }
		virtual inline void setScale     ( Vector2 scale )    { _scale = scale; }
		virtual inline void setRotation  ( Angle rotation )   { _rotation = rotation; }
		virtual inline void setBlendColor( Color blendColor ) { _blendColor = blendColor; }

		virtual Vector2 getSize( void ) const = 0;

		virtual inline Origin getOrigin( void ) const { return _origin; }
		virtual inline void setOrigin( Origin origin ) { _origin = origin; setOriginSize(getSize()); }

	}; // class DrawableComponent

} // namespace Arc

#endif // __ARC_DRAWABLE_COMPONENT_H__