#include "MouseSource.h"
#include "InputSystem.h"
#include "Program.h"

const Arc::EventType Arc::MouseSource::EVENT_MOUSE_MOVED      = "mouseMoved";
const Arc::EventType Arc::MouseSource::EVENT_MOUSE_PRESSED    = "mousePressed";
const Arc::EventType Arc::MouseSource::EVENT_MOUSE_RELEASED   = "mouseReleased";
const Arc::EventType Arc::MouseSource::EVENT_MOUSE_HELD       = "mouseHeld";
const Arc::EventType Arc::MouseSource::EVENT_MOUSE_WHEEL_UP   = "mouseWheelUp";
const Arc::EventType Arc::MouseSource::EVENT_MOUSE_WHEEL_DOWN = "mouseWheelDown";

Arc::MouseSource::MouseSource( void )
    : _sdlButtonStates(0),
      _buttonStates(),
      _mousePos(),
      _mouseDelta()
{

    for (unsigned int button = 0; button < NUM_MOUSE_BUTTONS; ++button)
    {
        _buttonStates.add((MouseButton)button, InputState());
    }

    gpEventDispatcher->addEventListener(Program::EVENT_UPDATE, this, &MouseSource::update);
}

Arc::MouseSource::~MouseSource( void )
{
    gpEventDispatcher->removeEventListener(Program::EVENT_UPDATE, this, &MouseSource::update);
}

void Arc::MouseSource::update( const Event& event )
{
    int
        x, y,
        dX, dY;

    SDL_PumpEvents();

	// Get the current mouse button states and the mouse position
    _sdlButtonStates = SDL_GetMouseState(&x, &y);
	
	// Get the mouse delta position
    SDL_GetRelativeMouseState(&dX, &dY);

    _mousePos.X = (float)x;
    _mousePos.Y = (float)y;

    _mouseDelta.X = (float)dX;
    _mouseDelta.Y = (float)dY;

	// Dispatch the EVENT_MOUSE_MOVED event if the mouse has moved
    if (_mouseDelta != Vector2::ZERO)
    {
        gpEventDispatcher->dispatchEvent(Event(MouseSource::EVENT_MOUSE_MOVED, MouseData(_mousePos, _mouseDelta)));
    }

    bool down;
    MouseButton button;
    InputState *pState;

    Map<MouseButton, InputState>::Iterator it;
    for (it = _buttonStates.begin(); it != _buttonStates.end(); ++it)
    {
        button =  it->first;
        pState = &it->second;

		// Get the current state of the button
        down = ((_sdlButtonStates & SDL_BUTTON(MouseToSDLMouse(button))) != 0);

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
            gpEventDispatcher->dispatchEvent(Event(MouseSource::EVENT_MOUSE_PRESSED, MouseData(_mousePos, _mouseDelta, button)));
        }
        else if (pState->Released)
        {
            gpEventDispatcher->dispatchEvent(Event(MouseSource::EVENT_MOUSE_RELEASED, MouseData(_mousePos, _mouseDelta, button)));
        }

        if (pState->Down)
        {
            gpEventDispatcher->dispatchEvent(Event(MouseSource::EVENT_MOUSE_HELD, MouseData(_mousePos, _mouseDelta, button)));
        }
    }
}

void Arc::MouseSource::handleSDLEvent( SDL_Event sdlEvent )
{
	switch (sdlEvent.type)
	{
	case SDL_MOUSEBUTTONDOWN:

		// Handle the SDL_BUTTON_WHEELUP and SDL_BUTTON_WHEELDOWN 'buttons' only available through the SDL event loop
		if (sdlEvent.button.button == SDL_BUTTON_WHEELUP)
		{
			gpEventDispatcher->dispatchEvent(Event(MouseSource::EVENT_MOUSE_WHEEL_UP, MouseData(_mousePos, _mouseDelta, MOUSE_BUTTON_WHEEL_UP)));
		}
		else if (sdlEvent.button.button == SDL_BUTTON_WHEELDOWN)
		{
			gpEventDispatcher->dispatchEvent(Event(MouseSource::EVENT_MOUSE_WHEEL_DOWN, MouseData(_mousePos, _mouseDelta, MOUSE_BUTTON_WHEEL_DOWN)));
		}

		break;
	}
}
