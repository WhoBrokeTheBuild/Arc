#include "GameObject.h"
#include "MemoryTracker.h"

void *Arc::GameObject::operator new( size_t size )
{
    return malloc(size);
}
void *Arc::GameObject::operator new[]( size_t size )
{
    return malloc(size);
}

void *Arc::GameObject::operator new( size_t size, int lineNumber, const char *filename )
{
    void* ptr = ::operator new(size);
    if (gpMemoryTracker)
        gpMemoryTracker->addAllocation((GameObject*)ptr, size, lineNumber, string(filename));
    return ptr;
}

void *Arc::GameObject::operator new[]( size_t size, int lineNumber, const char *filename )
{
    void* ptr = ::operator new(size);
    if (gpMemoryTracker)
        gpMemoryTracker->addAllocation((GameObject*)ptr, size, lineNumber, string(filename));
    return ptr;
}

void Arc::GameObject::operator delete( void *ptr, int lineNumber, const char *filename )
{
    ::operator delete(ptr);
    if (gpMemoryTracker)
        gpMemoryTracker->removeAllocation((GameObject*)ptr);
    free(ptr);
}

void Arc::GameObject::operator delete[]( void *ptr, int lineNumber, const char *filename )
{
    ::operator delete(ptr);
    if (gpMemoryTracker)
        gpMemoryTracker->removeAllocation((GameObject*)ptr);
    free(ptr);
}

void Arc::GameObject::operator delete( void *ptr )
{
    if (gpMemoryTracker)
        gpMemoryTracker->removeAllocation((GameObject*)ptr);
    free(ptr);
}

void Arc::GameObject::operator delete[]( void *ptr )
{
    if (gpMemoryTracker)
        gpMemoryTracker->removeAllocation((GameObject*)ptr);
    free(ptr);
}