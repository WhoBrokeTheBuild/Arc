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
	protected:

	public:

		Vector2
			Vel,
			Acc;

		PhysicsComponent( void );
		virtual inline ~PhysicsComponent( void ) { term (); }

		virtual void init( Vector2 vel = Vector2::ZERO, Vector2 acc = Vector2::ZERO );
		virtual inline void term( void ) { }

		virtual inline string toString( void ) const { return "Physics Component"; }

		virtual void update( const FrameData* data );

	}; // class PhysicsComponent

} // namespace Arc

#endif // __ARC_PHYSICS_COMPONENT_H__

