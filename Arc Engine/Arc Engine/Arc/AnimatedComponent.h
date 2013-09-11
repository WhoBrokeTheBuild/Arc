#pragma once

#ifndef __ARC_ANIMATED_COMPONENT_H__
#define __ARC_ANIMATED_COMPONENT_H__

#include "Common.h"
#include "Component.h"

namespace Arc
{
	class AnimatedComponent :
		public Component
	{
	public:

		AnimatedComponent( void );
		virtual inline ~AnimatedComponent( void ) { term (); }

		virtual void init( void );
		virtual void term( void );

		virtual inline string toString( void ) const { return "Animated Component"; }

	}; // class AnimatedComponent

} // namespace Arc

#endif // __ARC_ANIMATED_COMPONENT_H__