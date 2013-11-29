#include "PhysicsComponent.h"
#include "Unit.h"

const Arc::UnitComponentType Arc::PhysicsComponent::UNIT_CMP_TYPE_PHYSICS = "physics";

void Arc::PhysicsComponent::update( const FrameData* data )
{
	_pUnit->setPos(_pUnit->getPos() + Vel);
	Vel += Acc;
}
