#include "InputSystem.h"
#include "ArcApp.h"

InputSystem::InputSystem( void )
{
}

InputSystem::~InputSystem( void )
{
    term();
}

std::string InputSystem::toString( void ) const
{
    return "Input System";
}

void InputSystem::init( void )
{
    _pKeyboardSource = New KeyboardSource();
    _pKeyboardSource->init();

    _pMouseSource = New MouseSource();
    _pMouseSource->init();

    _pTextInputSource = New TextInputSource();
    _pTextInputSource->init();

    gpEventDispatcher->addEventListener(ArcApp::EVENT_UPDATE, this, &InputSystem::update);
}

void InputSystem::term( void )
{
    gpEventDispatcher->removeEventListener(ArcApp::EVENT_UPDATE, this, &InputSystem::update);

    delete _pTextInputSource;
    delete _pMouseSource;
    delete _pKeyboardSource;
}

void InputSystem::update( const Event& event )
{
    SDL_Event sdlEvent;

    while (SDL_PollEvent(&sdlEvent))
    {
        handleSDLEvent(sdlEvent);
    }
}

void InputSystem::handleSDLEvent( SDL_Event sdlEvent )
{
    switch (sdlEvent.type)
    {
    case SDL_QUIT:

        gpEventDispatcher->dispatchEvent(Event(ArcApp::EVENT_EXIT));

        break;
    }
}
