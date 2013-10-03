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

	public:

		ShapeComponent( Unit* pUnit, Point offset = Point::ZERO, Angle rotation = Angle::ZERO, Color blendColor = Color::WHITE, Point origin = Point::ZERO );
		virtual ~ShapeComponent( void );

		virtual inline void setTriangle ( float radius ) { _shape = SHAPE_TRIANGLE;  _radius = radius; }
		virtual inline void setRectangle( Size size )    { _shape = SHAPE_RECTANGLE; _size = size; }
		virtual inline void setPentagon ( float radius ) { _shape = SHAPE_PENTAGON;  _radius = radius; }
		virtual inline void setHexagon  ( float radius ) { _shape = SHAPE_HEXAGON;   _radius = radius; }
		virtual inline void setCircle   ( float radius ) { _shape = SHAPE_CIRCLE;    _radius = radius; }

		virtual inline string toString( void ) const { return "Shape Component"; }

		virtual void render( const RenderData* data );

	}; // class ShapeComponent

} // namespace Arc

#endif // __ARC_SHAPE_COMPONENT_H__

