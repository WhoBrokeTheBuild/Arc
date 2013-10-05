#pragma once

#ifndef __ARC_ANIMATED_COMPONENT_H__
#define __ARC_ANIMATED_COMPONENT_H__

#include "Common.h"
#include "DrawableComponent.h"

namespace Arc
{
	class AnimatedComponent :
		public DrawableComponent
	{
	public:

		AnimatedComponent( Unit* pUnit );
		virtual ~AnimatedComponent( void );

		virtual inline string toString( void ) const { return "Animated Component"; }

		virtual inline Vector2 getSize( void ) const { return Vector2::ZERO; }

	}; // class AnimatedComponent

} // namespace Arc

#endif // __ARC_ANIMATED_COMPONENT_H__
