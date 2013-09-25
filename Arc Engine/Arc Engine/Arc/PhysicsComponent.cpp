#include "PhysicsComponent.h"
#include "Unit.h"

Arc::PhysicsComponent::PhysicsComponent( Unit* pUnit, Vector2 vel /*= Vector2::ZERO*/, Vector2 acc /*= Vector2::ZERO */ )
    : Component(pUnit),
      Vel(vel),
      Acc(acc)
{
}

Arc::PhysicsComponent::~PhysicsComponent( void )
{
}

void Arc::PhysicsComponent::update( const FrameData* data )
{
	_pUnit->addToPos(Vel);
	Vel += Acc;
}
