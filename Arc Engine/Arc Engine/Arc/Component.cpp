#include "Component.h"
#include "Unit.h"

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
