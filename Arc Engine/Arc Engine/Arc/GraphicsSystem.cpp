#include "GraphicsSystem.h"

const Arc::EventType Arc::GraphicsSystem::EVENT_GRAPHICS_RESET = "graphicsReset";

Arc::GraphicsSystem::GraphicsSystem( void )
{
    _clearColor    = Color::BLACK;
    _pRenderTarget = nullptr;
    _screenBPP     = 0;
    _windowSize    = Size::ZERO;
    _windowTitle   = string();
    _fullscreen    = false;
}

void Arc::GraphicsSystem::init( Size windowSize, string windowTitle )
{
    INFO(toString(), "Initializing");

    _windowSize  = windowSize;
    _windowTitle = windowTitle;
    _fullscreen  = false;
    _clearColor  = Color::STORM;

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
    resetVideoMode();
    resetGL();

    _pRenderTarget = New RenderTarget();
    _pRenderTarget->init(this);

    if (TTF_Init() < 0)
    {
        ERROR(toString(), "Failed to initialize TTF Addon");
        die();
    }

    INFO(toString(), "Complete");
}

void Arc::GraphicsSystem::term( void )
{
    INFO(toString(), "Terminating");

    delete _pRenderTarget;

    TTF_Quit();
    SDL_Quit();

    INFO(toString(), "Complete");
}

void Arc::GraphicsSystem::setFullscreen( bool fullscreen )
{
    _fullscreen = fullscreen;

    resetVideoMode();
    resetGL();
}

void Arc::GraphicsSystem::setWindowSize( Size size )
{
    _windowSize = size;

    resetVideoMode();
    resetGL();
}

void Arc::GraphicsSystem::setWindowTitle( string title )
{
    _windowTitle = title;

    SDL_WM_SetCaption(_windowTitle.c_str(), nullptr);
}

void Arc::GraphicsSystem::setClearColor( Color clearColor )
{
    _clearColor = clearColor;
}

void Arc::GraphicsSystem::setWindowIcon( string filename )
{
    SDL_Surface *pSurface = IMG_Load(filename.c_str());

    if (!pSurface)
        ERRORF(toString(), "Cannot Load Icon File (%s)", filename);

    SDL_WM_SetIcon(pSurface, nullptr);

    SDL_FreeSurface(pSurface);
}

void Arc::GraphicsSystem::resetGL( void )
{
    glViewport(0, 0, (int)_windowSize.X, (int)_windowSize.Y);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glOrtho(0, (int)_windowSize.X, (int)_windowSize.Y, 0, 1, -1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glClearColor(_clearColor.fracR(), _clearColor.fracG(), _clearColor.fracB(), _clearColor.fracA());
    glClear(GL_COLOR_BUFFER_BIT);
    SDL_GL_SwapBuffers();

    GLenum error = glGetError();

    if (error != GL_NO_ERROR)
    {
        ERRORF(toString(), "Failed to initialize OpenGL (%s)", gluErrorString(error));
        die();
    }

    gpEventDispatcher->dispatchEvent(Event(EVENT_GRAPHICS_RESET));
}

void Arc::GraphicsSystem::resetVideoMode( void )
{
    unsigned int flags = 0;

    const SDL_VideoInfo* info = SDL_GetVideoInfo();

    if (!info)
    {
        ERRORF(toString(), "Failed to query SDL video info (%s)", SDL_GetError());
        die();
    }

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

    if (SDL_SetVideoMode((int)_windowSize.X, (int)_windowSize.Y, _screenBPP, flags) == nullptr)
    {
        ERRORF(toString(), "Failed to set SDL video mode (%s)", SDL_GetError());
        die();
    }
}
