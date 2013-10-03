#pragma once

#ifndef __ARC_DRAWABLE_H__
#define __ARC_DRAWABLE_H__

#include "Common.h"
#include "Component.h"

namespace Arc
{
	class DrawableComponent :
		public Component
	{
	protected:

		Point
			_offset,
			_origin;

		Angle
			_rotation;

		Color
			_blendColor;

	public:

		DrawableComponent( Unit* pUnit, Point offset = Point::ZERO, Angle rotation = Angle::ZERO, Color blendColor = Color::WHITE, Point origin = Point::ZERO );
		virtual ~DrawableComponent( void );

		virtual inline string toString( void ) const { return "Drawable Component"; }

		virtual inline Point getOffset    ( void ) const { return _offset; }
		virtual inline Point getOrigin    ( void ) const { return _origin; }
		virtual inline Angle getRotation  ( void ) const { return _rotation; }
		virtual inline Color getBlendColor( void ) const { return _blendColor; }
		
		virtual inline void setOffset    ( Point offset )     { _offset = offset; }
		virtual inline void setOrigin    ( Point origin )     { _origin = origin; }
		virtual inline void setRotation  ( Angle rotation )   { _rotation = rotation; }
		virtual inline void setBlendColor( Color blendColor ) { _blendColor = blendColor; }

	}; // class DrawableComponent

} // namespace Arc

#endif // __ARC_DRAWABLE_H__