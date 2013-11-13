#include "InputSystem.h"
#include "Program.h"

Arc::InputSystem::InputSystem( void )
{
    INFO(toString(), "Initializing");

    _pKeyboardSource  = New KeyboardSource();
    _pMouseSource     = New MouseSource();

    gpEventDispatcher->addEventListener(Program::EVENT_UPDATE, this, &InputSystem::update);

    INFO(toString(), "Complete");
}

Arc::InputSystem::~InputSystem( void )
{
    INFO(toString(), "Terminating");

    gpEventDispatcher->removeEventListener(Program::EVENT_UPDATE, this, &InputSystem::update);

    delete _pMouseSource;
    delete _pKeyboardSource;

    INFO(toString(), "Complete");
}

void Arc::InputSystem::update( const Event& event )
{
    SDL_Event sdlEvent;

	// SDL Event Loop, without this the window won't respond
    while (SDL_PollEvent(&sdlEvent))
    {
        handleSDLEvent(sdlEvent);
    }
}

void Arc::InputSystem::handleSDLEvent( SDL_Event sdlEvent )
{
    switch (sdlEvent.type)
    {
    case SDL_QUIT: // Handle the SDL event when the window is closed

        gpEventDispatcher->dispatchEvent(Event(Program::EVENT_EXIT));

        break;
	}
	_pMouseSource->handleSDLEvent(sdlEvent);
	_pKeyboardSource->handleSDLEvent(sdlEvent);
}
