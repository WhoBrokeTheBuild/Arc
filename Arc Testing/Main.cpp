#include "Common.h"

#include <Arc/Console.h>
#include <Arc/MemoryTracker.h>

#include "TestApp.h"

int main(int argc, char *argv[])
{
#ifdef DEBUG

    initConsole();

#endif

    INFO("Main", "Starting Up");

    gpMemoryTracker = new MemoryTracker();

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
        Arc::pause();
    }

#endif

    delete gpMemoryTracker;
    gpMemoryTracker = nullptr;

    return EXIT_SUCCESS;
}
