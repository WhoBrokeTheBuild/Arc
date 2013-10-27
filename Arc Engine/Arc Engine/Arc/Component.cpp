#include "Component.h"
#include "Unit.h"

const ComponentType Arc::Component::CMP_TYPE_BASE = "base";

Arc::Component::Component( Unit* pUnit )
    : _pUnit(pUnit)
{
}

Arc::Component::~Component( void)
{
}

bool Arc::Component::removeSelf( void )
{
    return getUnit()->removeComponent(this);
}
