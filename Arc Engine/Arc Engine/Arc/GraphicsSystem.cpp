#include "GraphicsSystem.h"

const Arc::SystemComponentType Arc::GraphicsSystem::SYS_CMP_TYPE_GRAPHICS = "graphics";

const Arc::EventType Arc::GraphicsSystem::EVENT_CLEAR_COLOR_CHANGED  = "graphicsSystem.clearColorChanged";
const Arc::EventType Arc::GraphicsSystem::EVENT_WINDOW_SIZE_CHANGED	 = "graphicsSystem.windowSizeChanged";
const Arc::EventType Arc::GraphicsSystem::EVENT_WINDOW_TITLE_CHANGED = "graphicsSystem.windowTitleChanged";
const Arc::EventType Arc::GraphicsSystem::EVENT_WINDOW_ICON_CHANGED  = "graphicsSystem.windowIconChanged";
const Arc::EventType Arc::GraphicsSystem::EVENT_FULLSCREEN_CHANGED	 = "graphicsSystem.fullscreenChanged";
const Arc::EventType Arc::GraphicsSystem::EVENT_GRAPHICS_RESET       = "graphicsSystem.graphicsReset";

Arc::GraphicsSystem::GraphicsSystem( Program* pProgram, Size windowSize, string windowTitle, Color clearColor, bool fullscreen )
	: SystemComponent(pProgram),
	  _clearColor(clearColor),
      _pRenderTarget(nullptr),
	  _screenBPP(),
	  _windowSize(windowSize),
	  _windowTitle(windowTitle),
	  _fullscreen(fullscreen)
{
    INFO(toString(), "Initializing");

	addType(SYS_CMP_TYPE_GRAPHICS);

	// Set SDL/OpenGL constants
    SDL_GL_SetAttribute(SDL_GL_RED_SIZE,           8);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE,         8);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE,          8);
    SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE,         8);

    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE,         24);
    SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE,        32);

    SDL_GL_SetAttribute(SDL_GL_ACCUM_RED_SIZE,     8);
    SDL_GL_SetAttribute(SDL_GL_ACCUM_GREEN_SIZE,   8);
    SDL_GL_SetAttribute(SDL_GL_ACCUM_BLUE_SIZE,    8);
    SDL_GL_SetAttribute(SDL_GL_ACCUM_ALPHA_SIZE,   8);

    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER,       1);

    setWindowTitle(_windowTitle);
    resetVideoMode(); // Create the window
    resetGL(); // Initialize OpenGL

    _pRenderTarget = New RenderTarget(this);

    if (TTF_Init() < 0) // Initialize the SDL TTF Addon for loading Fonts
    {
        ERROR(toString(), "Failed to initialize TTF Addon");
        die();
    }

    INFO(toString(), "Complete");
}

Arc::GraphicsSystem::~GraphicsSystem( void )
{
    INFO(toString(), "Terminating");

    delete _pRenderTarget;

    TTF_Quit();
    SDL_Quit(); // Cleanup SDL

    INFO(toString(), "Complete");
}

void Arc::GraphicsSystem::setFullscreen( bool fullscreen )
{
    _fullscreen = fullscreen;

    resetVideoMode();
	resetGL();

	dispatchEvent(Event(EVENT_FULLSCREEN_CHANGED));
}

void Arc::GraphicsSystem::setWindowSize( Size size )
{
	_windowSize = size;

    resetVideoMode();
	resetGL();

	dispatchEvent(Event(EVENT_WINDOW_SIZE_CHANGED));
}

void Arc::GraphicsSystem::setWindowTitle( string title )
{
    _windowTitle = title;

	SDL_WM_SetCaption(_windowTitle.c_str(), nullptr);

	dispatchEvent(Event(EVENT_WINDOW_TITLE_CHANGED));
}

void Arc::GraphicsSystem::setWindowIcon( string filename )
{
    SDL_Surface *pSurface = IMG_Load(filename.c_str());

    if ( ! pSurface)
        ERRORF(toString(), "Cannot Load Icon File (%s)", filename.c_str());

    SDL_WM_SetIcon(pSurface, nullptr);

    SDL_FreeSurface(pSurface);

	dispatchEvent(Event(EVENT_WINDOW_ICON_CHANGED));
}

void Arc::GraphicsSystem::resetGL( void )
{
	// Setup OpenGL for drawing 2D
    glViewport(0, 0, (int)_windowSize.X, (int)_windowSize.Y);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glOrtho(0, (int)_windowSize.X, (int)_windowSize.Y, 0, 1, -1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

	// Enable blending and set the blending function for scaling
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Clear the background to the clear color
    glClearColor(_clearColor.getFracR(), _clearColor.getFracG(), _clearColor.getFracB(), _clearColor.getFracA());
    glClear(GL_COLOR_BUFFER_BIT);
    SDL_GL_SwapBuffers();

    GLenum error = glGetError();

	// Handle any errors
    if (error != GL_NO_ERROR)
    {
        ERRORF(toString(), "Failed to initialize OpenGL (%s)", gluErrorString(error));
        die();
    }

	// Tell any textures or fonts to reload their data
    dispatchEvent(Event(EVENT_GRAPHICS_RESET));
}

void Arc::GraphicsSystem::resetVideoMode( void )
{
    unsigned int flags = 0;

	// Query current video capabilities
    const SDL_VideoInfo* info = SDL_GetVideoInfo();

    if ( ! info)
    {
        ERRORF(toString(), "Failed to query SDL video info (%s)", SDL_GetError());
        die();
    }

	// Set flags based on current video capabilities
    _screenBPP = info->vfmt->BitsPerPixel;

    flags |= SDL_OPENGL;
    flags |= SDL_DOUBLEBUF;
    flags |= SDL_HWPALETTE;

    if (info->hw_available)
    {
        flags |= SDL_HWSURFACE;
    }
    else
    {
        flags |= SDL_SWSURFACE;
    }

    if (info->blit_hw)
    {
        flags |= SDL_HWACCEL;
    }

    if (_fullscreen)
    {
        flags |= SDL_FULLSCREEN;
    }

	// Initialize SDL with the requested video settings and handle errors
    if (SDL_SetVideoMode((int)_windowSize.X, (int)_windowSize.Y, _screenBPP, flags) == nullptr)
    {
        ERRORF(toString(), "Failed to set SDL video mode (%s)", SDL_GetError());
        die();
    }
}
