#include "PhysicsComponent.h"
#include "Unit.h"

Arc::PhysicsComponent::PhysicsComponent(void)
{
	Vel = Acc = Vector2::ZERO;
}

void Arc::PhysicsComponent::init( Vector2 vel /*= Vector2::ZERO*/, Vector2 acc /*= Vector2::ZERO */ )
{
	Vel = vel;
	Acc = acc;
}

void Arc::PhysicsComponent::update( const FrameData* data )
{
	_pUnit->Pos += Vel;
	Vel += Acc;
}