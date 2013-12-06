#include "GraphicalProgram.h"

const Arc::EventType Arc::GraphicalProgram::EVENT_INPUT_SYSTEM_INITIALIZED    = "graphicalProgram.inputSystemInitialized";
const Arc::EventType Arc::GraphicalProgram::EVENT_INPUT_SYSTEM_TERMINATED     = "graphicalProgram.inputSystemTerminated";
const Arc::EventType Arc::GraphicalProgram::EVENT_AUDIO_SYSTEM_INITIALIZED    = "graphicalProgram.audioSystemInitialized";
const Arc::EventType Arc::GraphicalProgram::EVENT_AUDIO_SYSTEM_TERMINATED     = "graphicalProgram.audioSystemTerminated";
const Arc::EventType Arc::GraphicalProgram::EVENT_GRAPHICS_SYSTEM_INITIALIZED = "graphicalProgram.graphicsSystemInitialized";
const Arc::EventType Arc::GraphicalProgram::EVENT_GRAPHICS_SYSTEM_TERMINATED  = "graphicalProgram.graphicsSystemTerminated";

const Arc::EventType Arc::GraphicalProgram::EVENT_UPDATE_START = "graphicalProgram.updateStart";
const Arc::EventType Arc::GraphicalProgram::EVENT_UPDATE       = "graphicalProgram.update";
const Arc::EventType Arc::GraphicalProgram::EVENT_UPDATE_END   = "graphicalProgram.updateEnd";
const Arc::EventType Arc::GraphicalProgram::EVENT_RENDER_START = "graphicalProgram.renderStart";
const Arc::EventType Arc::GraphicalProgram::EVENT_RENDER       = "graphicalProgram.render";
const Arc::EventType Arc::GraphicalProgram::EVENT_RENDER_END   = "graphicalProgram.renderEnd";
const Arc::EventType Arc::GraphicalProgram::EVENT_EXIT         = "graphicalProgram.exit";

Arc::GraphicalProgram::GraphicalProgram( Size windowSize /*= Size(640.0f, 480.0f)*/, string windowTitle /*= "Arc"*/, Color clearColor /*= Color::BLACK*/, bool fullscreen /*= false */ )
	: Program()
{
	initSDL();
	initGraphicsSystem(windowSize, windowTitle, clearColor, fullscreen);
	initInputSystem();
	initEventHandlers();

	_targetFPS  = 60.0f;
	_currentFPS = 0;
}

Arc::GraphicalProgram::~GraphicalProgram( void )
{
	termEventHandlers();
	termGraphicsSystem();
	termAudioSystem();
	termInputSystem();
	termSDL();
}

void Arc::GraphicalProgram::initSDL( void )
{
	if (SDL_Init(SDL_INIT_EVERYTHING) > 0)
	{
		ERRORF(toString(), "Failed to initialize SDL (%s)", SDL_GetError());
		die();
	}
}

void Arc::GraphicalProgram::termSDL( void )
{
	SDL_Quit();
}

void Arc::GraphicalProgram::initEventHandlers( void )
{
	addEventListener(EVENT_UPDATE_START, this, &GraphicalProgram::eventUpdateStart);
	addEventListener(EVENT_UPDATE,       this, &GraphicalProgram::eventUpdate);
	addEventListener(EVENT_UPDATE_END,   this, &GraphicalProgram::eventUpdateEnd);
	addEventListener(EVENT_RENDER_START, this, &GraphicalProgram::eventRenderStart);
	addEventListener(EVENT_RENDER,       this, &GraphicalProgram::eventRender);
	addEventListener(EVENT_RENDER_END,   this, &GraphicalProgram::eventRenderEnd);

	addEventListener(EVENT_EXIT, this, &GraphicalProgram::eventExit);
}

void Arc::GraphicalProgram::termEventHandlers( void )
{
	addEventListener(EVENT_UPDATE_START, this, &GraphicalProgram::eventUpdateStart);
	addEventListener(EVENT_UPDATE,       this, &GraphicalProgram::eventUpdate);
	addEventListener(EVENT_UPDATE_END,   this, &GraphicalProgram::eventUpdateEnd);
	addEventListener(EVENT_RENDER_START, this, &GraphicalProgram::eventRenderStart);
	addEventListener(EVENT_RENDER,       this, &GraphicalProgram::eventRender);
	addEventListener(EVENT_RENDER_END,   this, &GraphicalProgram::eventRenderEnd);

	removeEventListener(EVENT_EXIT, this, &GraphicalProgram::eventExit);
}

void Arc::GraphicalProgram::initGraphicsSystem( Size windowSize /*= Size(640.0f, 480.0f)*/, string windowTitle /*= "Arc"*/, Color clearColor /*= Color::BLACK*/, bool fullscreen /*= false */ )
{
	delete getSystemOfType<GraphicsSystem>(GraphicsSystem::SYS_CMP_TYPE_GRAPHICS);
	_systems.add(New GraphicsSystem(this, windowSize, windowTitle, clearColor, fullscreen));
	dispatchEvent(Event(EVENT_GRAPHICS_SYSTEM_INITIALIZED));
}

void Arc::GraphicalProgram::initAudioSystem( void )
{
	delete getSystemOfType<AudioSystem>(AudioSystem::SYS_CMP_TYPE_AUDIO);
	_systems.add(New AudioSystem(this));
	dispatchEvent(Event(EVENT_AUDIO_SYSTEM_INITIALIZED));
}

void Arc::GraphicalProgram::initInputSystem( void )
{
	delete getSystemOfType<InputSystem>(InputSystem::SYS_CMP_TYPE_INPUT);
	_systems.add(New InputSystem(this));
	dispatchEvent(Event(EVENT_INPUT_SYSTEM_INITIALIZED));
}

void Arc::GraphicalProgram::termGraphicsSystem( void )
{
	GraphicsSystem* pSys = getSystemOfType<GraphicsSystem>(GraphicsSystem::SYS_CMP_TYPE_GRAPHICS);

	if (pSys != nullptr)
	{
		delete pSys;
		_systems.remove(pSys);
		dispatchEvent(Event(EVENT_GRAPHICS_SYSTEM_TERMINATED));
	}
}

void Arc::GraphicalProgram::termAudioSystem( void )
{
	AudioSystem* pSys = getSystemOfType<AudioSystem>(AudioSystem::SYS_CMP_TYPE_AUDIO);

	if (pSys != nullptr)
	{
		delete pSys;
		_systems.remove(pSys);
		dispatchEvent(Event(EVENT_AUDIO_SYSTEM_TERMINATED));
	}
}

void Arc::GraphicalProgram::termInputSystem( void )
{
	InputSystem* pSys = getSystemOfType<InputSystem>(InputSystem::SYS_CMP_TYPE_INPUT);

	if (pSys != nullptr)
	{
		delete pSys;
		_systems.remove(pSys);
		dispatchEvent(Event(EVENT_INPUT_SYSTEM_TERMINATED));
	}
}

void Arc::GraphicalProgram::start( void )
{
	_running = true;

	double
		fpsDelay = 0,
		frameDelay = 1;

	_currentFPS = 1; // Prevent divide-by-zero errors in deltaTime

	FrameTime* pFrameTime = New FrameTime();

	FrameData frameData = FrameData(pFrameTime);
	RenderData renderData = RenderData(getGraphicsSystem()->getRenderTarget());

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
		pFrameTime->update(frameDelay, _currentFPS, _targetFPS);

		updateFrame(frameData);

		if (getGraphicsSystem() != nullptr)
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

void Arc::GraphicalProgram::stop( void )
{
	_running = false;
}

void Arc::GraphicalProgram::updateFrame( const FrameData& frameData )
{
	processSDLEvents();

	dispatchEvent(Event(GraphicalProgram::EVENT_UPDATE_START, frameData));
	dispatchEvent(Event(GraphicalProgram::EVENT_UPDATE,       frameData));
	dispatchEvent(Event(GraphicalProgram::EVENT_UPDATE_END,   frameData));
}

void Arc::GraphicalProgram::renderFrame( const RenderData& renderData )
{
	renderData.getRenderTarget()->beginDraw();

	dispatchEvent(Event(GraphicalProgram::EVENT_RENDER_START, renderData));
	dispatchEvent(Event(GraphicalProgram::EVENT_RENDER,       renderData));
	dispatchEvent(Event(GraphicalProgram::EVENT_RENDER_END,   renderData));

	renderData.getRenderTarget()->endDraw();
}

void Arc::GraphicalProgram::processSDLEvents()
{
	SDL_Event sdlEvent;

	// SDL Event Loop, without this the window won't respond
	while (SDL_PollEvent(&sdlEvent))
	{
		switch (sdlEvent.type)
		{
		case SDL_QUIT: // Handle the SDL event when the window is closed

			dispatchEvent(Event(GraphicalProgram::EVENT_EXIT));

			break;
		}

		InputSystem* pSys = getInputSystem();
		if (pSys != nullptr)
			pSys->handleSDLEvent(sdlEvent);
	}
}
