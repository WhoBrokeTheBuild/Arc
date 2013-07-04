
#include <ArcCommon.h>
#include <Console.h>
#include <MemoryTracker.h>
#include <ArcApp.h>

#pragma comment(lib, "Arc Engine.lib")
#pragma comment(lib, "SDL.lib")
#pragma comment(lib, "SDLmain.lib")
#pragma comment(lib, "SDL_image.lib")
#pragma comment(lib, "SDL_mixer.lib")
#pragma comment(lib, "SDL_ttf.lib")
#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glu32.lib")

#include "Map.h"

int main(int argc, char *argv[])
{

#ifdef DEBUG

    init_console();

#endif

    Map<string, int> numbers;

    numbers.add("one", 1)->add("two", 2)->add("three", 3);

    Map<string, int>::Iterator it;
    for (it = numbers.begin(); it != numbers.end(); ++it)
        cout << it->first << " = " << it->second << endl;

    cout << "has one?  " << numbers.contains("one") << endl;
    cout << "has two?  " << numbers.contains("two") << endl;
    cout << "has four? " << numbers.contains("four") << endl;

    cout << "has 1? " << numbers.containsValue(1) << endl;
    cout << "has 2? " << numbers.containsValue(2) << endl;
    cout << "has 4? " << numbers.containsValue(4) << endl;

    ArrayList<string> keys = numbers.keyArrayList();

    for (unsigned int i = 0; i < keys.size(); ++i)
        cout << keys[i] << endl;

    LinkedList<int> values = numbers.valueLinkedList();

    LinkedList<int>::Iterator it2;
    for (it2 = values.begin(); it2 != values.end(); ++it2)
        cout << *it2 << endl;

    Queue<string> strings = *Queue<string>().push("hello")->push("world");

    while (!strings.empty())
        cout << strings.pop() << endl;

    die();

    INF("Main", "Starting Up");

    gpMemoryTracker = new MemoryTracker();

    ArcApp *program = New ArcApp();
    program->init();

    INF("Main", "Starting Game Loop");

    program->start();

    INF("Main", "Shutting Down");

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