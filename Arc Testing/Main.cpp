#include "Common.h"

#include <Arc/Console.h>
#include <Arc/MemoryTracker.h>

#include "TestApp.h"

int main(int argc, char *argv[])
{
#ifdef DEBUG

    initConsole();

#endif

    /*
    fstream out("vector2.test", ios::out | ios::binary | ios::trunc);

    Vector2 test(25.0f, 32.0f);
    string  test2("Hello, World!");

    cout << test << endl;
    test.serialize(out);

    cout << test2 << endl;
    streamWriteString(test2, out);

    out.close();
    fstream in("vector2.test", ios::in | ios::binary);

    Vector2 other;
    string other2;

    other.deserialize(in);
    cout << other << endl;

    streamReadString(other2, in);
    cout << other2 << endl;

    in.close();

    die();
    */

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
