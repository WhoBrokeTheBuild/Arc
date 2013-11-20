#include "PhysicsComponent.h"
#include "Unit.h"

const Arc::ComponentType Arc::PhysicsComponent::CMP_TYPE_PHYSICS = "physics";

void Arc::PhysicsComponent::update( const FrameData* data )
{
	_pUnit->addToPos(Vel);
	Vel += Acc;
}
