#include "GraphicsSystem.h"

const EventType GraphicsSystem::EVENT_GRAPHICS_RESET = "graphicsReset";

GraphicsSystem::GraphicsSystem( void )
{
}

GraphicsSystem::~GraphicsSystem( void )
{
    term();
}

void GraphicsSystem::init( Size windowSize, string windowTitle )
{
    INF(toString(), "Initializing");

    _windowSize  = windowSize;
    _windowTitle = windowTitle;
    _fullscreen  = false;
    _clearColor  = Color::STORM;
    _screenBPP   = 32;

    if (SDL_Init(SDL_INIT_EVERYTHING) > 0)
    {
        ERR(toString(), "Failed to initialize SDL");
        die();
    }

    SDL_GL_SetAttribute(SDL_GL_RED_SIZE,           8);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE,         8);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE,          8);
    SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE,         8);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE,         16);
    SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE,        32);
    SDL_GL_SetAttribute(SDL_GL_ACCUM_RED_SIZE,     8);
    SDL_GL_SetAttribute(SDL_GL_ACCUM_GREEN_SIZE,   8);
    SDL_GL_SetAttribute(SDL_GL_ACCUM_BLUE_SIZE,    8);
    SDL_GL_SetAttribute(SDL_GL_ACCUM_ALPHA_SIZE,   8);

    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 2);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER,       1);

    setWindowTitle(_windowTitle);
    resetVideoMode();
    resetGL();

    _pRenderTarget = New RenderTarget();
    _pRenderTarget->init(this);

    if (TTF_Init() < 0)
    {
        ERR(toString(), "Failed to initialize TTF Addon");
        die();
    }

    INF(toString(), "Complete");
}

void GraphicsSystem::term( void )
{
    delete _pRenderTarget;

    TTF_Quit();
    SDL_Quit();
}

std::string GraphicsSystem::toString( void ) const
{
    return "Graphics System";
}

void GraphicsSystem::setFullscreen( bool fullscreen )
{
    _fullscreen = fullscreen;

    resetVideoMode();
    resetGL();
}

void GraphicsSystem::setWindowSize( Size size )
{
    _windowSize = size;

    resetVideoMode();
    resetGL();
}

void GraphicsSystem::setWindowTitle( string title )
{
    _windowTitle = title;

    SDL_WM_SetCaption(_windowTitle.c_str(), nullptr);
}

void GraphicsSystem::setClearColor( Color clearColor )
{
    _clearColor = clearColor;
}

void GraphicsSystem::setWindowIcon( string filename )
{
    SDL_Surface *pSurface = IMG_Load(filename.c_str());

    if (!pSurface)
    {
        stringstream ss;

        ss << "Cannot Load Icon File: " << filename;

        ERR(toString(), ss.str());
    }

    SDL_WM_SetIcon(pSurface, nullptr);

    SDL_FreeSurface(pSurface);
}

void GraphicsSystem::resetGL( void )
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
        stringstream ss;
        ss << "Failed to initialize OpenGL (" << gluErrorString(error) << ")";

        ERR(toString(), ss.str());
        die();
    }

    gpEventDispatcher->dispatchEvent(Event(EVENT_GRAPHICS_RESET));
}

void GraphicsSystem::resetVideoMode( void )
{
    int flags = 0;

    flags |= SDL_HWSURFACE;
    flags |= SDL_GL_DOUBLEBUFFER;
    flags |= SDL_OPENGL;

    if (_fullscreen)
    {
        flags |= SDL_FULLSCREEN;
    }

    if (SDL_SetVideoMode((int)_windowSize.X, (int)_windowSize.Y, _screenBPP, flags) == nullptr)
    {
        ERR(toString(), "Failed to set SDL video mode");
        die();
    }
}