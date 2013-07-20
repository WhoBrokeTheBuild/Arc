#include "Common.h"

#include <Arc/Console.h>
#include <Arc/MemoryTracker.h>

#include "TestApp.h"

#ifdef WINDOWS

#pragma comment(lib, "Arc Engine.lib")
#pragma comment(lib, "SDL.lib")
#pragma comment(lib, "SDLmain.lib")
#pragma comment(lib, "SDL_image.lib")
#pragma comment(lib, "SDL_mixer.lib")
#pragma comment(lib, "SDL_ttf.lib")
#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glu32.lib")

#endif

int main(int argc, char *argv[])
{
#ifdef DEBUG

    Arc::init_console();

#endif

    INFO("Main", "Starting Up");

    gpMemoryTracker = new Arc::MemoryTracker();

    TestApp *program = New TestApp();
    program->init();

    INFO("Main", "Starting Game Loop");

    program->start();

    INFO("Main", "Shutting Down");

    delete program;

#ifdef DEBUG

    if (gpMemoryTracker->numAllocations() > 0)
    {
        gpMemoryTracker->printAllocations();
        pause();
    }

    delete gpMemoryTracker;
    gpMemoryTracker = nullptr;

#endif

    return 0;
}
