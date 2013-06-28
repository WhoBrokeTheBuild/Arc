#include "Unit.h"

Unit::Unit(void)
{
}

Unit::~Unit(void)
{
}

std::string Unit::toString( void ) const
{
    return "Unit";
}

void Unit::init( Vector2 pos /*= Vector2::ZERO*/, Vector2 origin /*= Vector2::ZERO*/, float rot /*= 0.0f*/, Color blendColor /*= Color::WHITE*/, float depth /*= 1.0f*/ )
{
    Pos = pos;
    Origin = origin;
    Rot = rot;
    BlendColor = blendColor;
    Depth = depth;

    gpEventDispatcher->addEventListener(ArcApp::EVENT_FRAME,  this, &Unit::update);
    gpEventDispatcher->addEventListener(ArcApp::EVENT_RENDER, this, &Unit::render);
}

void Unit::term( void )
{
    gpEventDispatcher->removeEventListener(ArcApp::EVENT_FRAME,  this, &Unit::update);
    gpEventDispatcher->removeEventListener(ArcApp::EVENT_RENDER, this, &Unit::render);
}

void Unit::update( const Event& event )
{
    //const FrameData* frameData = event.dataAs<FrameData>();
}

void Unit::render( const Event& event )
{
    //const RenderData* renderData = event.dataAs<RenderData>();
}

Rect Unit::bounds( void )
{
    return Rect(Pos, UnitSize);
}
