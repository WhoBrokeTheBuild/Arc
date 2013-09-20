#include "Component.h"
#include "Unit.h"

Arc::Component::Component( void )
{
    _pUnit = nullptr;
}

void Arc::Component::init( Unit* parent )
{
    _pUnit = parent;
}

void Arc::Component::term( void )
{
}

bool Arc::Component::removeSelf( void )
{
    return getUnit()->removeComponent(this);
}
