#include "UnitComponent.h"
#include "Unit.h"

const Arc::UnitComponentType Arc::UnitComponent::UNIT_CMP_TYPE_BASE = "base";

bool Arc::UnitComponent::removeSelf( void )
{
    return getUnit()->removeComponent(this);
}
