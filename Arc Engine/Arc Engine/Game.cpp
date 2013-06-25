#include "Game.h"
#include "PlayerIndex.h"

const EventType Game::EVENT_ENTER_FRAME  = "enterFrame";
const EventType Game::EVENT_FRAME        = "frame";
const EventType Game::EVENT_EXIT_FRAME   = "exitFrame";
const EventType Game::EVENT_RENDER_START = "renderStart";
const EventType Game::EVENT_RENDER       = "render";
const EventType Game::EVENT_RENDER_END   = "renderEnd";
const EventType Game::EVENT_GAME_START   = "gameStart";
const EventType Game::EVENT_GAME_END     = "gameEnd";

Game::Game( void )
{
}

Game::~Game( void )
{
    term();
}

std::string Game::toString( void ) const
{
    return "Game";
}

void Game::init( void )
{
    INF(toString(), "Starting Init");

    _targetFPS = 60.0f;
    _currentFPS = 0;

    gpEventDispatcher = New EventDispatcher();

    _pGraphicsSystem = New GraphicsSystem();
    _pGraphicsSystem->init();

    _pInputSystem = New InputSystem();
    _pInputSystem->init();

    gpEventDispatcher->addEventListener(Game::EVENT_FRAME,    this, &Game::update);
    gpEventDispatcher->addEventListener(Game::EVENT_RENDER,   this, &Game::render);
    gpEventDispatcher->addEventListener(Game::EVENT_GAME_END, this, &Game::stop);

    INF(toString(), "Finished Init");
}

void Game::term( void )
{
    INF(toString(), "Terminating");

    gpEventDispatcher->removeEventListener(Game::EVENT_GAME_END, this, &Game::stop);
    gpEventDispatcher->removeEventListener(Game::EVENT_RENDER,   this, &Game::render);
    gpEventDispatcher->removeEventListener(Game::EVENT_FRAME,    this, &Game::update);

    delete _pInputSystem;
    delete _pGraphicsSystem;

    delete gpEventDispatcher;
}

void Game::start( void )
{
    _running = true;

    gpEventDispatcher->dispatchEvent(Event(Game::EVENT_GAME_START));

    double 
        fpsDelay = 1000.0 / _targetFPS,
        frameDelay = 0;

    FrameData frameData = FrameData();
    RenderData renderData = RenderData(_pGraphicsSystem->renderTarget());

    Timer fpsTimer = Timer();
    fpsTimer.start();

    stringstream ss;

    while (_running)
    {
        frameData.update(frameDelay, _currentFPS, _targetFPS);

        updateFrame(frameData);
        renderFrame(renderData);

        _currentFPS = (float)(1000.0 / frameDelay);

        fpsTimer.sleepUntilElapsed(fpsDelay);
        frameDelay = fpsTimer.getElapsedMilli();
        fpsTimer.start();
    }
}

void Game::stop ( const Event& event )
{
    _running = false;
}

void Game::updateFrame( const FrameData& frameData )
{
    gpEventDispatcher->dispatchEvent(Event(Game::EVENT_ENTER_FRAME, frameData));
    gpEventDispatcher->dispatchEvent(Event(Game::EVENT_FRAME,       frameData));
    gpEventDispatcher->dispatchEvent(Event(Game::EVENT_EXIT_FRAME,  frameData));
}

void Game::renderFrame( const RenderData& renderData )
{
    renderData.renderTarget()->beginDraw();

    gpEventDispatcher->dispatchEvent(Event(Game::EVENT_RENDER_START, renderData));
    gpEventDispatcher->dispatchEvent(Event(Game::EVENT_RENDER,       renderData));
    gpEventDispatcher->dispatchEvent(Event(Game::EVENT_RENDER_END,   renderData));

    renderData.renderTarget()->endDraw();
}

void Game::update( const Event& event )
{
}

void Game::render( const Event& event )
{
}
