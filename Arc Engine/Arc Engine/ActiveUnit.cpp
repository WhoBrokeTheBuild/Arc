#include "ActiveUnit.h"
#include "InputSystem.h"

ActiveUnit::~ActiveUnit( void )
{
    term();
}

std::string ActiveUnit::toString( void ) const
{
    return "Active Unit";
}

void ActiveUnit::init( Animation* pAnimation /*= nullptr*/, Vector2 pos /*= Vector2::ZERO*/, Vector2 vel /*= Vector2::ZERO*/, Vector2 acc /*= Vector2::ZERO*/, Vector2 origin /*= Vector2::ZERO*/, float rot /*= 0.0f*/, Color blendColor /*= Color::WHITE*/, float depth /*= 1.0f */ )
{
    AnimatedUnit::init(pAnimation, pos, origin, rot, blendColor, depth);

    Vel = vel;
    Acc = acc;
}

void ActiveUnit::term( void )
{
}

void ActiveUnit::update( const Event& event )
{
    AnimatedUnit::update(event);

    const FrameData* frameData = event.dataAs<FrameData>();

    updateMovement(frameData);
}

void ActiveUnit::updateMovement( const FrameData* frameData )
{
    Pos += Vel;
    Vel += Acc;
}
