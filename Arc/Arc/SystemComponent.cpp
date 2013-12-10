#include "SystemComponent.h"
#include "Program.h"

const Arc::SystemComponentType Arc::SystemComponent::SYS_CMP_TYPE_BASE = "base";

Arc::Program* Arc::SystemComponent::getProgram( void )
{
	return _pProgram;
}
