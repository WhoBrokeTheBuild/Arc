#include "Component.h"
#include "Unit.h"

Arc::Component::Component( void )
{
    _pParent = nullptr;
}

void Arc::Component::init( Unit* parent )
{
    _pParent = parent;
}

void Arc::Component::term( void )
{
}

bool Arc::Component::removeSelf( void )
{
    return getParentUnit()->removeComponent(this);
}
