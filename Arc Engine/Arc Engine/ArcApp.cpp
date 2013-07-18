#include "ArcApp.h"

const EventType ArcApp::EVENT_UPDATE_START = "updateStart";
const EventType ArcApp::EVENT_UPDATE       = "update";
const EventType ArcApp::EVENT_UPDATE_END   = "updateEnd";
const EventType ArcApp::EVENT_RENDER_START = "renderStart";
const EventType ArcApp::EVENT_RENDER       = "render";
const EventType ArcApp::EVENT_RENDER_END   = "renderEnd";
const EventType ArcApp::EVENT_EXIT         = "exit";

ArcApp::ArcApp( void )
{
}

ArcApp::~ArcApp( void )
{
    term();
}

std::string ArcApp::toString( void ) const
{
    return "Game";
}

void ArcApp::init( Size windowSize /*= Size(640, 480)*/, string windowTitle /*= "Arc"*/ )
{
    INF(toString(), "Starting Init");

    gpEventDispatcher = New EventDispatcher();

    _targetFPS  = 60.0f;
    _currentFPS = 0;

    initGraphics(windowSize, windowTitle);
    initInput();
    initAudio();

    gpEventDispatcher->addEventListener(ArcApp::EVENT_UPDATE,  this, &ArcApp::update);
    gpEventDispatcher->addEventListener(ArcApp::EVENT_RENDER, this, &ArcApp::render);
    gpEventDispatcher->addEventListener(ArcApp::EVENT_EXIT,   this, &ArcApp::stop);

    INF(toString(), "Finished Init");
}

void ArcApp::term( void )
{
    INF(toString(), "Terminating");

    gpEventDispatcher->removeEventListener(ArcApp::EVENT_EXIT,   this, &ArcApp::stop);
    gpEventDispatcher->removeEventListener(ArcApp::EVENT_RENDER, this, &ArcApp::render);
    gpEventDispatcher->removeEventListener(ArcApp::EVENT_UPDATE,  this, &ArcApp::update);

    delete _pInputSystem;
    delete _pGraphicsSystem;

    delete gpEventDispatcher;
}

void ArcApp::start( void )
{
    _running = true;

    double
        fpsDelay = 1000.0 / _targetFPS,
        frameDelay = 1;

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

void ArcApp::stop ( const Event& event )
{
    _running = false;
}

void ArcApp::updateFrame( const FrameData& frameData )
{
    gpEventDispatcher->dispatchEvent(Event(ArcApp::EVENT_UPDATE_START, frameData));
    gpEventDispatcher->dispatchEvent(Event(ArcApp::EVENT_UPDATE,       frameData));
    gpEventDispatcher->dispatchEvent(Event(ArcApp::EVENT_UPDATE_END,   frameData));
}

void ArcApp::renderFrame( const RenderData& renderData )
{
    renderData.renderTarget()->beginDraw();

    gpEventDispatcher->dispatchEvent(Event(ArcApp::EVENT_RENDER_START, renderData));
    gpEventDispatcher->dispatchEvent(Event(ArcApp::EVENT_RENDER,       renderData));
    gpEventDispatcher->dispatchEvent(Event(ArcApp::EVENT_RENDER_END,   renderData));

    renderData.renderTarget()->endDraw();
}

void ArcApp::initGraphics( Size windowSize, string windowTitle )
{
    _pGraphicsSystem = New GraphicsSystem();
    _pGraphicsSystem->init(windowSize, windowTitle);
}

void ArcApp::initInput( void )
{
    _pInputSystem = New InputSystem();
    _pInputSystem->init();
}

void ArcApp::initAudio( void )
{

}
