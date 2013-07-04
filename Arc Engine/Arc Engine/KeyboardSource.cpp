#include "KeyboardSource.h"
#include "ArcApp.h"

const EventType KeyboardSource::EVENT_KEY_PRESSED  = "keyPressed";
const EventType KeyboardSource::EVENT_KEY_RELEASED = "keyReleased";
const EventType KeyboardSource::EVENT_KEY_HELD     = "keyHeld";

KeyboardSource::KeyboardSource( void )
{
}

KeyboardSource::~KeyboardSource( void )
{
    term();
}

std::string KeyboardSource::toString( void ) const
{
    return "Keyboard Controller";
}

void KeyboardSource::init( void )
{
    _sdlKeys = nullptr;

    for (unsigned int key = 0; key < NUM_KEYS; ++key)
    {
        _keyStates.add((KeyboardKey)key, InputState());
    }

    gpEventDispatcher->addEventListener(ArcApp::EVENT_FRAME, this, &KeyboardSource::update);
}

void KeyboardSource::term( void )
{
    gpEventDispatcher->removeEventListener(ArcApp::EVENT_FRAME, this, &KeyboardSource::update);
}

void KeyboardSource::update( const Event& event )
{
    _sdlKeys = SDL_GetKeyState(nullptr);

    bool down;
    KeyboardKey key;
    InputState *pState;

    KeyStateMap::Iterator it;
    for (it = _keyStates.begin(); it != _keyStates.end(); ++it)
    {
        key    =  it->first;
        pState = &it->second;

        down = (_sdlKeys[KeyToSDLKey(key)] == TRUE);

        pState->Pressed  = false;
        pState->Released = false;

        if (down && !pState->Down)
        {
            pState->Pressed = true;
        }
        else if (!down && pState->Down)
        {
            pState->Released = true;
        }

        pState->Down = down;

        if (pState->Pressed)
        {
            gpEventDispatcher->dispatchEvent(Event(KeyboardSource::EVENT_KEY_PRESSED, KeyData(key)));
        }
        else if (pState->Released)
        {
            gpEventDispatcher->dispatchEvent(Event(KeyboardSource::EVENT_KEY_RELEASED, KeyData(key)));
        }

        if (pState->Down)
        {
            gpEventDispatcher->dispatchEvent(Event(KeyboardSource::EVENT_KEY_HELD, KeyData(key)));
        }
    }
}
