#include "Program.h"

Arc::Program* Arc::Program::_pInstance = nullptr;

const Arc::EventType Arc::Program::EVENT_UPDATE_START = "updateStart";
const Arc::EventType Arc::Program::EVENT_UPDATE       = "update";
const Arc::EventType Arc::Program::EVENT_UPDATE_END   = "updateEnd";
const Arc::EventType Arc::Program::EVENT_RENDER_START = "renderStart";
const Arc::EventType Arc::Program::EVENT_RENDER       = "render";
const Arc::EventType Arc::Program::EVENT_RENDER_END   = "renderEnd";
const Arc::EventType Arc::Program::EVENT_EXIT         = "exit";

Arc::Program::Program( void )
	: _pGraphicsSystem(nullptr),
	  _pInputSystem(nullptr),
	  _pAudioSystem(nullptr),
	  _pNetworkSystem(nullptr),
	  _running(),
	  _targetFPS(),
	  _currentFPS()
{
}

void Arc::Program::init( Size windowSize /*= Size(640, 480)*/, string windowTitle /*= "Arc"*/ )
{
    INFO(toString(), "Initializing");

    gpEventDispatcher = New EventDispatcher();

    _targetFPS  = 60.0f;
    _currentFPS = 0;

    initRandom();

    gpEventDispatcher->addEventListener(Program::EVENT_UPDATE, this, &Program::update);
    gpEventDispatcher->addEventListener(Program::EVENT_RENDER, this, &Program::render);
    gpEventDispatcher->addEventListener(Program::EVENT_EXIT,   this, &Program::stop);

    INFO(toString(), "Complete");
}

void Arc::Program::term( void )
{
    INFO(toString(), "Terminating");

    gpEventDispatcher->removeEventListener(Program::EVENT_EXIT,   this, &Program::stop);
    gpEventDispatcher->removeEventListener(Program::EVENT_RENDER, this, &Program::render);
    gpEventDispatcher->removeEventListener(Program::EVENT_UPDATE, this, &Program::update);

    delete _pNetworkSystem;
    delete _pScriptingSystem;
    delete _pInputSystem;
    delete _pAudioSystem;
    delete _pGraphicsSystem;

    delete gpEventDispatcher;

    INFO(toString(), "Complete");
}

void Arc::Program::start( void )
{
    _running = true;

    double
        fpsDelay = 1000.0 / _targetFPS, // The milliseconds to sleep each frame
        frameDelay = 1;

    _currentFPS = 1; // Prevent divide-by-zero errors in deltaTime

    FrameData frameData = FrameData();
    RenderData renderData = RenderData(_pGraphicsSystem->getRenderTarget());

    Timer fpsTimer = Timer();
    fpsTimer.start();

    INFO(toString(), "Starting Loop");

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

void Arc::Program::stop ( const Event& event )
{
    _running = false;
}

void Arc::Program::updateFrame( const FrameData& frameData )
{
    gpEventDispatcher->dispatchEvent(Event(Program::EVENT_UPDATE_START, frameData));
    gpEventDispatcher->dispatchEvent(Event(Program::EVENT_UPDATE,       frameData));
    gpEventDispatcher->dispatchEvent(Event(Program::EVENT_UPDATE_END,   frameData));
}

void Arc::Program::renderFrame( const RenderData& renderData )
{
    renderData.renderTarget()->beginDraw();

    gpEventDispatcher->dispatchEvent(Event(Program::EVENT_RENDER_START, renderData));
    gpEventDispatcher->dispatchEvent(Event(Program::EVENT_RENDER,       renderData));
    gpEventDispatcher->dispatchEvent(Event(Program::EVENT_RENDER_END,   renderData));

    renderData.renderTarget()->endDraw();
}

void Arc::Program::initAll( Size windowSize, string windowTitle )
{
    initCore();
    initInput();
    initGraphics(windowSize, windowTitle);
    initAudio();
    initScripting();
    initNetworking();
}

void Arc::Program::initCore( void )
{
    if (SDL_Init(SDL_INIT_EVERYTHING) > 0)
    {
        ERRORF(toString(), "Failed to initialize SDL (%s)", SDL_GetError());
        die();
    }
}

void Arc::Program::initGraphics( Size windowSize, string windowTitle )
{
    _pGraphicsSystem = New GraphicsSystem();
    _pGraphicsSystem->init(windowSize, windowTitle);
}

void Arc::Program::initAudio( void )
{
    _pAudioSystem = New AudioSystem();
    _pAudioSystem->init();
}

void Arc::Program::initInput( void )
{
    _pInputSystem = New InputSystem();
    _pInputSystem->init();
}

void Arc::Program::initScripting( void )
{
    _pScriptingSystem = New ScriptingSystem();
    _pScriptingSystem->init();
}

void Arc::Program::initNetworking( void )
{
    _pNetworkSystem = New NetworkSystem();
    _pNetworkSystem->init();
}
