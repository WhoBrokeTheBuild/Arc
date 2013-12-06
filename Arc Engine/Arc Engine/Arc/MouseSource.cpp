#include "MouseSource.h"
#include "InputSystem.h"
#include "GraphicalProgram.h"

const Arc::EventType Arc::MouseSource::EVENT_MOUSE_MOVED      = "mouseSource.mouseMoved";
const Arc::EventType Arc::MouseSource::EVENT_MOUSE_PRESSED    = "mouseSource.mousePressed";
const Arc::EventType Arc::MouseSource::EVENT_MOUSE_RELEASED   = "mouseSource.mouseReleased";
const Arc::EventType Arc::MouseSource::EVENT_MOUSE_HELD       = "mouseSource.mouseHeld";
const Arc::EventType Arc::MouseSource::EVENT_MOUSE_WHEEL_UP   = "mouseSource.mouseWheelUp";
const Arc::EventType Arc::MouseSource::EVENT_MOUSE_WHEEL_DOWN = "mouseSource.mouseWheelDown";

Arc::MouseSource::MouseSource( InputSystem* pInputSystem )
    : _pInputSystem(pInputSystem),
	  _sdlButtonStates(0),
      _buttonStates(),
      _mousePos(),
      _mouseDelta()
{

    for (unsigned int button = 0; button < NUM_MOUSE_BUTTONS; ++button)
    {
        _buttonStates.add((MouseButton)button, InputState());
    }

    GraphicalProgram::getInstance()->addEventListener(GraphicalProgram::EVENT_UPDATE, this, &MouseSource::eventUpdate);
}

Arc::MouseSource::~MouseSource( void )
{
    GraphicalProgram::getInstance()->removeEventListener(GraphicalProgram::EVENT_UPDATE, this, &MouseSource::eventUpdate);
}

void Arc::MouseSource::eventUpdate( const Event& event )
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
        _pInputSystem->dispatchEvent(Event(MouseSource::EVENT_MOUSE_MOVED, MouseData(_mousePos, _mouseDelta)));
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
            _pInputSystem->dispatchEvent(Event(MouseSource::EVENT_MOUSE_PRESSED, MouseData(_mousePos, _mouseDelta, button)));
        }
        else if (pState->Released)
        {
            _pInputSystem->dispatchEvent(Event(MouseSource::EVENT_MOUSE_RELEASED, MouseData(_mousePos, _mouseDelta, button)));
        }

        if (pState->Down)
        {
            _pInputSystem->dispatchEvent(Event(MouseSource::EVENT_MOUSE_HELD, MouseData(_mousePos, _mouseDelta, button)));
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
			_pInputSystem->dispatchEvent(Event(MouseSource::EVENT_MOUSE_WHEEL_UP, MouseData(_mousePos, _mouseDelta, MOUSE_BUTTON_WHEEL_UP)));
		}
		else if (sdlEvent.button.button == SDL_BUTTON_WHEELDOWN)
		{
			_pInputSystem->dispatchEvent(Event(MouseSource::EVENT_MOUSE_WHEEL_DOWN, MouseData(_mousePos, _mouseDelta, MOUSE_BUTTON_WHEEL_DOWN)));
		}

		break;
	}
}
