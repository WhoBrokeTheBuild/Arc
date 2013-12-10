#include "KeyboardSource.h"
#include "InputSystem.h"
#include "GraphicalProgram.h"

const Arc::EventType Arc::KeyboardSource::EVENT_KEY_PRESSED  = "keyboardSource.keyPressed";
const Arc::EventType Arc::KeyboardSource::EVENT_KEY_RELEASED = "keyboardSource.keyReleased";
const Arc::EventType Arc::KeyboardSource::EVENT_KEY_HELD     = "keyboardSource.keyHeld";

Arc::KeyboardSource::KeyboardSource( InputSystem* pInputSystem )
    : _pInputSystem(pInputSystem),
	  _sdlKeys(nullptr),
      _keyStates()
{
    for (unsigned int key = 0; key < NUM_KEYS; ++key)
    {
        _keyStates.add((KeyboardKey)key, InputState());
    }

    GraphicalProgram::getInstance()->addEventListener(GraphicalProgram::EVENT_UPDATE, this, &KeyboardSource::eventUpdate);
}

Arc::KeyboardSource::~KeyboardSource( void )
{
    GraphicalProgram::getInstance()->removeEventListener(GraphicalProgram::EVENT_UPDATE, this, &KeyboardSource::eventUpdate);
}

void Arc::KeyboardSource::eventUpdate( const Event& event )
{
	// Get the current state of all keys
    _sdlKeys = SDL_GetKeyState(nullptr);

    bool down;
    KeyboardKey key;
    InputState *pState;

	// Loop over all supported keys
    Map<KeyboardKey, InputState>::Iterator it;
    for (it = _keyStates.begin(); it != _keyStates.end(); ++it)
    {
        key    =  it->first;
        pState = &it->second;

		// Get current state of the key
        down = (_sdlKeys[KeyToSDLKey(key)] == 1);

		// Reset state values
        pState->Pressed  = false;
        pState->Released = false;

		// Set other state values based on current and previous states
        if (down && !pState->Down)
        {
            pState->Pressed = true;
        }
        else if ( ! down && pState->Down)
        {
            pState->Released = true;
        }

        pState->Down = down;

		// Dispatch events based on state
        if (pState->Pressed)
        {
            _pInputSystem->dispatchEvent(Event(KeyboardSource::EVENT_KEY_PRESSED, KeyData(key)));
        }
        else if (pState->Released)
        {
            _pInputSystem->dispatchEvent(Event(KeyboardSource::EVENT_KEY_RELEASED, KeyData(key)));
        }

        if (pState->Down)
        {
            _pInputSystem->dispatchEvent(Event(KeyboardSource::EVENT_KEY_HELD, KeyData(key)));
        }
    }
}

void Arc::KeyboardSource::handleSDLEvent( SDL_Event sdlEvent )
{
}
