#include "InputSystem.h"
#include "Program.h"

Arc::InputSystem::InputSystem( void )
{
    _pKeyboardSource  = nullptr;
    _pMouseSource     = nullptr;
    _pTextInputSource = nullptr;
}

std::string Arc::InputSystem::toString( void ) const
{
    return "Input System";
}

void Arc::InputSystem::init( void )
{
    INFO(toString(), "Initializing");

    _pKeyboardSource = New KeyboardSource();
    _pKeyboardSource->init();

    _pMouseSource = New MouseSource();
    _pMouseSource->init();

    _pTextInputSource = New TextInputSource();
    _pTextInputSource->init();

    gpEventDispatcher->addEventListener(Program::EVENT_UPDATE, this, &InputSystem::update);

    INFO(toString(), "Complete");
}

void Arc::InputSystem::term( void )
{
    INFO(toString(), "Terminating");

    gpEventDispatcher->removeEventListener(Program::EVENT_UPDATE, this, &InputSystem::update);

    delete _pTextInputSource;
    delete _pMouseSource;
    delete _pKeyboardSource;

    INFO(toString(), "Complete");
}

void Arc::InputSystem::update( const Event& event )
{
    SDL_Event sdlEvent;

    while (SDL_PollEvent(&sdlEvent))
    {
        handleSDLEvent(sdlEvent);
    }
}

void Arc::InputSystem::handleSDLEvent( SDL_Event sdlEvent )
{
    switch (sdlEvent.type)
    {
    case SDL_QUIT:

        gpEventDispatcher->dispatchEvent(Event(Program::EVENT_EXIT));

        break;
    }
}
