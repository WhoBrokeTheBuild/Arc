#include "Unit.h"
#include "Layer.h"
#include "Scene.h"

Arc::Unit::Unit( void )
{
    _pParent = nullptr;
    Pos      = Point::ZERO;
    Depth    = 0.0f;
}

void Arc::Unit::init( Vector2 pos, float depth /*= 0.0f */ )
{
    Pos = pos;
    Depth = depth;
}

Arc::Scene* Arc::Unit::getParentScene( void )
{
    return _pParent->getParentScene();
}

