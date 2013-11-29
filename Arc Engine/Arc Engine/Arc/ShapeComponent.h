#pragma once

#ifndef __ARC_SHAPE_COMPONENT_H__
#define __ARC_SHAPE_COMPONENT_H__

#include "Common.h"
#include "DrawableComponent.h"

#include "Shapes.h"

namespace Arc
{
	class ShapeComponent :
		public DrawableComponent
	{
	protected:

		Shapes
			_shape;

		Size
			_size;

		float
			_radius;

		bool
			_filled;

	public:

		static const UnitComponentType UNIT_CMP_TYPE_SHAPE;

		ShapeComponent( Unit* pUnit,
						bool filled = false,
			            Color blendColor = Color::WHITE,
			            Origin origin = Origin::ZERO,
			            Vector2 scale = Vector2::ONE, 
			            Angle rotation = Angle::ZERO,
			            Point offset = Point::ZERO )
			: DrawableComponent(pUnit, blendColor, origin, scale, rotation, offset),
			  _shape(INVALID_SHAPE),
			  _filled(filled),
			  _size(),
			  _radius()
		{
			addType(UNIT_CMP_TYPE_SHAPE);
		}

		virtual inline ~ShapeComponent( void ) { }

		virtual inline void setRectangle( Size size )    { _shape = SHAPE_RECTANGLE; _size = size;     setOriginSize(getSize()); }
		virtual inline void setTriangle ( float radius ) { _shape = SHAPE_TRIANGLE;  _radius = radius; setOriginSize(getSize()); }
		virtual inline void setPentagon ( float radius ) { _shape = SHAPE_PENTAGON;  _radius = radius; setOriginSize(getSize()); }
		virtual inline void setHexagon  ( float radius ) { _shape = SHAPE_HEXAGON;   _radius = radius; setOriginSize(getSize()); }
		virtual inline void setCircle   ( float radius ) { _shape = SHAPE_CIRCLE;    _radius = radius; setOriginSize(getSize()); }

		virtual inline string toString( void ) const { return "Shape Component"; }

		virtual void render( const RenderData* data );

		virtual Vector2 getSize( void ) const;

		inline bool isFilled ( void ) const { return _filled; }
		inline void setFilled( bool filled ) { _filled = filled; }

	}; // class ShapeComponent

} // namespace Arc

#endif // __ARC_SHAPE_COMPONENT_H__

