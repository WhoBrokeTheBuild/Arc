#include "MouseSource.h"
#include "ArcApp.h"

const EventType MouseSource::EVENT_MOUSE_MOVED    = "mouseMoved";
const EventType MouseSource::EVENT_MOUSE_PRESSED  = "mousePressed";
const EventType MouseSource::EVENT_MOUSE_RELEASED = "mouseReleased";
const EventType MouseSource::EVENT_MOUSE_HELD     = "mouseHeld";

MouseSource::MouseSource( void )
{
}

MouseSource::~MouseSource( void )
{
    term();
}

std::string MouseSource::toString( void ) const
{
    return "Mouse Controller";
}

void MouseSource::init( void )
{
    for (unsigned int button = 0; button < NUM_MOUSE_BUTTONS; ++button)
    {
        _buttonStates.add((MouseButton)button, InputState());
    }

    gpEventDispatcher->addEventListener(ArcApp::EVENT_FRAME, this, &MouseSource::update);
}

void MouseSource::term( void )
{
    gpEventDispatcher->removeEventListener(ArcApp::EVENT_FRAME, this, &MouseSource::update);
}

void MouseSource::update( const Event& event )
{
    int
        x, y,
        dX, dY;

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

    MouseStateMap::Iterator it;
    for (it = _buttonStates.begin(); it != _buttonStates.end(); ++it)
    {
        button =  it->first;
        pState = &it->second;

        down =  ((_sdlButtonStates & SDL_BUTTON(MouseToSDLMouse(button))) == true);

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
