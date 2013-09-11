#pragma once

#ifndef __ARC_PHYSICS_COMPONENT_H__
#define __ARC_PHYSICS_COMPONENT_H__

#include "Common.h"
#include "Component.h"

namespace Arc
{
	class PhysicsComponent :
		public Component
	{
	public:

		PhysicsComponent( void );
		virtual inline ~PhysicsComponent( void ) { term (); }

		virtual void init( void );
		virtual void term( void );

		virtual inline string toString( void ) const { return "Physics Component"; }

	}; // class PhysicsComponent

} // namespace Arc

#endif // __ARC_PHYSICS_COMPONENT_H__

