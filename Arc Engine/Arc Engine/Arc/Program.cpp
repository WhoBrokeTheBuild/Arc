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
	  _pScriptingSystem(nullptr),
	  _pNetworkSystem(nullptr),
	  _running(),
	  _targetFPS(),
	  _currentFPS()
{
    INFO(toString(), "Initializing");

	_pInstance = this;

	// Create the global event dispatcher
    gpEventDispatcher = New EventDispatcher();

    _targetFPS  = 60.0f;
    _currentFPS = 0;

    initRandom();

    gpEventDispatcher->addEventListener(Program::EVENT_UPDATE_START, this, &Program::updateStart);
    gpEventDispatcher->addEventListener(Program::EVENT_UPDATE,       this, &Program::update);
    gpEventDispatcher->addEventListener(Program::EVENT_UPDATE_END,   this, &Program::updateEnd);
    gpEventDispatcher->addEventListener(Program::EVENT_RENDER_START, this, &Program::renderStart);
    gpEventDispatcher->addEventListener(Program::EVENT_RENDER,       this, &Program::render);
    gpEventDispatcher->addEventListener(Program::EVENT_RENDER_END,   this, &Program::renderEnd);
	gpEventDispatcher->addEventListener(Program::EVENT_EXIT,         this, &Program::stop);

	addEventListener(Program::EVENT_EXIT, this, &Program::stop);

    INFO(toString(), "Complete");
}

Arc::Program::~Program( void )
{
    INFO(toString(), "Terminating");

	removeEventListener(Program::EVENT_EXIT, this, &Program::stop);

    gpEventDispatcher->removeEventListener(Program::EVENT_EXIT,         this, &Program::stop);
    gpEventDispatcher->removeEventListener(Program::EVENT_RENDER_END,   this, &Program::renderEnd);
    gpEventDispatcher->removeEventListener(Program::EVENT_RENDER,       this, &Program::render);
    gpEventDispatcher->removeEventListener(Program::EVENT_RENDER_START, this, &Program::renderStart);
    gpEventDispatcher->removeEventListener(Program::EVENT_UPDATE_END,   this, &Program::updateEnd);
    gpEventDispatcher->removeEventListener(Program::EVENT_UPDATE,       this, &Program::update);
    gpEventDispatcher->removeEventListener(Program::EVENT_UPDATE_START, this, &Program::updateStart);

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
        fpsDelay = 0,
        frameDelay = 1;

    _currentFPS = 1; // Prevent divide-by-zero errors in deltaTime

    FrameData frameData = FrameData();
	RenderData renderData = RenderData(nullptr);
	
	if (_pGraphicsSystem != nullptr)
		renderData = RenderData(_pGraphicsSystem->getRenderTarget());

    Timer fpsTimer = Timer();
    fpsTimer.start();

    INFO(toString(), "Starting Loop");

    while (_running)
    {
		// The milliseconds to sleep each frame
		if (_targetFPS == -1)
			fpsDelay = -1;
		else
			fpsDelay = 1000.0 / _targetFPS;

		// Update the frame data to calculate a new delta time
        frameData.update(frameDelay, _currentFPS, _targetFPS);

        updateFrame(frameData);
		
		if (_pGraphicsSystem != nullptr)
			renderFrame(renderData);

		// Calculate current FPS based on the time last frame took
        _currentFPS = (float)(1000.0 / frameDelay);

		// If FPS is capped
		if (fpsDelay != -1)
		{
			// Delay the program for the time needed to stay at the target FPS
			fpsTimer.sleepUntilElapsed(fpsDelay);

			// Get how long the timer had to sleep
			frameDelay = fpsTimer.getElapsedMilli();

			// Reset the timer 
			fpsTimer.start();
		}
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
    renderData.getRenderTarget()->beginDraw();

    gpEventDispatcher->dispatchEvent(Event(Program::EVENT_RENDER_START, renderData));
    gpEventDispatcher->dispatchEvent(Event(Program::EVENT_RENDER,       renderData));
    gpEventDispatcher->dispatchEvent(Event(Program::EVENT_RENDER_END,   renderData));

    renderData.getRenderTarget()->endDraw();
}

void Arc::Program::initAll( Size windowSize, string windowTitle, Color clearColor /*= Color::BLACK*/ )
{
    initCore();
    initInput();
    initGraphics(windowSize, windowTitle, clearColor);
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

void Arc::Program::initGraphics( Size windowSize, string windowTitle, Color clearColor /*= Color::BLACK*/ )
{
	delete _pGraphicsSystem;
    _pGraphicsSystem = New GraphicsSystem(windowSize, windowTitle, clearColor);
}

void Arc::Program::initAudio( void )
{
	delete _pAudioSystem;
    _pAudioSystem = New AudioSystem();
}

void Arc::Program::initInput( void )
{
	delete _pInputSystem;
    _pInputSystem = New InputSystem();
}

void Arc::Program::initScripting( void )
{
	delete _pScriptingSystem;
    _pScriptingSystem = New ScriptingSystem();
}

void Arc::Program::initNetworking( void )
{
	delete _pNetworkSystem;
    _pNetworkSystem = New NetworkSystem();
}
