#include "KeyboardSource.h"
#include "Program.h"

const Arc::EventType Arc::KeyboardSource::EVENT_KEY_PRESSED  = "keyPressed";
const Arc::EventType Arc::KeyboardSource::EVENT_KEY_RELEASED = "keyReleased";
const Arc::EventType Arc::KeyboardSource::EVENT_KEY_HELD     = "keyHeld";

Arc::KeyboardSource::KeyboardSource( void )
{
    _sdlKeys   = nullptr;
    _keyStates = Map<KeyboardKey, InputState>();
}

void Arc::KeyboardSource::init( void )
{
    _sdlKeys = nullptr;

    for (unsigned int key = 0; key < NUM_KEYS; ++key)
    {
        _keyStates.add((KeyboardKey)key, InputState());
    }

    gpEventDispatcher->addEventListener(Program::EVENT_UPDATE, this, &KeyboardSource::update);
}

void Arc::KeyboardSource::term( void )
{
    gpEventDispatcher->removeEventListener(Program::EVENT_UPDATE, this, &KeyboardSource::update);
}

void Arc::KeyboardSource::update( const Event& event )
{
    _sdlKeys = SDL_GetKeyState(nullptr);

    bool down;
    KeyboardKey key;
    InputState *pState;

    Map<KeyboardKey, InputState>::Iterator it;
    for (it = _keyStates.begin(); it != _keyStates.end(); ++it)
    {
        key    =  it->first;
        pState = &it->second;

        down = (_sdlKeys[KeyToSDLKey(key)] == 1);

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
