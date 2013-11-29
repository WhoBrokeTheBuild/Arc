#include "InputSystem.h"
#include "GraphicalProgram.h"

const Arc::SystemComponentType Arc::InputSystem::SYS_CMP_TYPE_INPUT = "input";

Arc::InputSystem::InputSystem( Program* pProgram )
	: SystemComponent(pProgram)
{
    INFO(toString(), "Initializing");

	addType(SYS_CMP_TYPE_INPUT);

    _pKeyboardSource = New KeyboardSource(this);
    _pMouseSource = New MouseSource(this);

    GraphicalProgram::getInstance()->addEventListener(GraphicalProgram::EVENT_UPDATE, this, &InputSystem::eventUpdate);

    INFO(toString(), "Complete");
}

Arc::InputSystem::~InputSystem( void )
{
    INFO(toString(), "Terminating");

    GraphicalProgram::getInstance()->removeEventListener(GraphicalProgram::EVENT_UPDATE, this, &InputSystem::eventUpdate);

    delete _pMouseSource;
    delete _pKeyboardSource;

    INFO(toString(), "Complete");
}

void Arc::InputSystem::eventUpdate( const Event& event )
{
}

void Arc::InputSystem::handleSDLEvent( SDL_Event sdlEvent )
{
	_pMouseSource->handleSDLEvent(sdlEvent);
	_pKeyboardSource->handleSDLEvent(sdlEvent);
}
