#pragma once

#ifndef __ARC_SHAPE_COMPONENT_H__
#define __ARC_SHAPE_COMPONENT_H__

#include "Common.h"
#include "Component.h"

namespace Arc
{
	class ShapeComponent :
		public Component
	{
	public:

		ShapeComponent( void );
		virtual inline ~ShapeComponent( void ) { term (); }

		virtual void init( void );
		virtual void term( void );

		virtual inline string toString( void ) const { return "Shape Component"; }

	}; // class ShapeComponent

} // namespace Arc

#endif // __ARC_SHAPE_COMPONENT_H__

