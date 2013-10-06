#pragma once

#ifndef __ARC_DRAWABLE_COMPONENT_H__
#define __ARC_DRAWABLE_COMPONENT_H__

#include "Common.h"
#include "Component.h"

#include "OriginLocation.h"

namespace Arc
{
	class DrawableComponent :
		public Component
	{
	protected:

		OriginLocation
			_originLocation;

		Point
			_offset,
			_origin;

		Vector2
			_scale;

		Angle
			_rotation;

		Color
			_blendColor;

		virtual void calcOriginLocation( void );

	public:

		DrawableComponent( Unit* pUnit,
			               Point offset = Point::ZERO, 
			               Point origin = Point::ZERO, 
			               Vector2 scale = Vector2::ONE,
			               Angle rotation = Angle::ZERO, 
			               Color blendColor = Color::WHITE );
		DrawableComponent( Unit* pUnit,
			               Point offset = Point::ZERO,
			               OriginLocation originLocation = OriginLocation::ORIGIN_LOCATION_TOP_LEFT,
			               Vector2 scale = Vector2::ONE,
			               Angle rotation = Angle::ZERO,
			               Color blendColor = Color::WHITE );
		virtual ~DrawableComponent( void );

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

		virtual inline Point getOrigin( void ) const { return _origin; }
		virtual void         setOrigin( Point origin );

		virtual inline OriginLocation getOriginLocation( void ) const { return _originLocation; }
		virtual void                  setOriginLocation( OriginLocation originLocation );

	}; // class DrawableComponent

} // namespace Arc

#endif // __ARC_DRAWABLE_COMPONENT_H__