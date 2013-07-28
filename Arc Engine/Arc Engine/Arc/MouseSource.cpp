#include "MouseSource.h"
#include "Program.h"

const Arc::EventType Arc::MouseSource::EVENT_MOUSE_MOVED    = "mouseMoved";
const Arc::EventType Arc::MouseSource::EVENT_MOUSE_PRESSED  = "mousePressed";
const Arc::EventType Arc::MouseSource::EVENT_MOUSE_RELEASED = "mouseReleased";
const Arc::EventType Arc::MouseSource::EVENT_MOUSE_HELD     = "mouseHeld";

Arc::MouseSource::MouseSource( void )
{
    _sdlButtonStates = 0;
    _buttonStates    = Map<MouseButton, InputState>();
    _mousePos        = Point::ZERO;
    _mouseDelta      = Vector2::ZERO;
}

void Arc::MouseSource::init( void )
{
    for (unsigned int button = 0; button < NUM_MOUSE_BUTTONS; ++button)
    {
        _buttonStates.add((MouseButton)button, InputState());
    }

    gpEventDispatcher->addEventListener(Program::EVENT_UPDATE, this, &MouseSource::update);
}

void Arc::MouseSource::term( void )
{
    gpEventDispatcher->removeEventListener(Program::EVENT_UPDATE, this, &MouseSource::update);
}

void Arc::MouseSource::update( const Event& event )
{
    int
        x, y,
        dX, dY;

    SDL_PumpEvents();
    _sdlButtonStates = SDL_GetMouseState(&x, &y);
    SDL_GetRelativeMouseState(&dX, &dY);

    _mousePos.X = (float)x;
    _mousePos.Y = (float)y;

    _mouseDelta.X = (float)dX;
    _mouseDelta.Y = (float)dY;

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

        down =  ((_sdlButtonStates & SDL_BUTTON(MouseToSDLMouse(button))) != 0);

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
