#include "Component.h"
#include "Unit.h"

const Arc::ComponentType Arc::Component::CMP_TYPE_BASE = "base";

bool Arc::Component::removeSelf( void )
{
    return getUnit()->removeComponent(this);
}
