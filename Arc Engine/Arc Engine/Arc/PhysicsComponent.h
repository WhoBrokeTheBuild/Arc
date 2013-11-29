#pragma once

#ifndef __ARC_PHYSICS_COMPONENT_H__
#define __ARC_PHYSICS_COMPONENT_H__

#include "Common.h"
#include "UnitComponent.h"

namespace Arc
{
	class PhysicsComponent :
		public UnitComponent
	{
	protected:

	public:

		static const UnitComponentType UNIT_CMP_TYPE_PHYSICS;

		Vector2 Vel;
		Vector2 Acc;

		PhysicsComponent( Unit* pUnit, Vector2 vel = Vector2::ZERO, Vector2 acc = Vector2::ZERO )
			: UnitComponent(pUnit),
			  Vel(vel),
			  Acc(acc)
		{
			addType(UNIT_CMP_TYPE_PHYSICS);
		}

		virtual inline ~PhysicsComponent( void ) { }

		virtual inline string toString( void ) const { return "Physics Component"; }

		virtual void update( const FrameData* data );

	}; // class PhysicsComponent

} // namespace Arc

#endif // __ARC_PHYSICS_COMPONENT_H__

