#include "GameObject.h"
#include "MemoryTracker.h"

GameObject::GameObject( void )
{
}

GameObject::~GameObject( void )
{
}

ostream& operator<<( ostream& os, const GameObject& go )
{
    os << go.toString();
    return os;
}

void *GameObject::operator new(size_t size)
{
    return malloc(size);
}
void *GameObject::operator new[](size_t size)
{
    return malloc(size);
}

void *GameObject::operator new(size_t size, int lineNumber, const char *filename)
{
    void* ptr = ::operator new(size);
    if (gpMemoryTracker)
        gpMemoryTracker->addAllocation((GameObject*)ptr, size, lineNumber, string(filename));
    return ptr;
}

void *GameObject::operator new[](size_t size, int lineNumber, const char *filename)
{
    void* ptr = ::operator new(size);
    if (gpMemoryTracker)
        gpMemoryTracker->addAllocation((GameObject*)ptr, size, lineNumber, string(filename));
    return ptr;
}

void GameObject::operator delete(void *ptr, int lineNumber, const char *filename)
{
    ::operator delete(ptr);
    if (gpMemoryTracker)
        gpMemoryTracker->removeAllocation((GameObject*)ptr);
    free(ptr);
}

void GameObject::operator delete[](void *ptr, int lineNumber, const char *filename)
{
    ::operator delete(ptr);
    if (gpMemoryTracker)
        gpMemoryTracker->removeAllocation((GameObject*)ptr);
    free(ptr);
}

void GameObject::operator delete(void *ptr)
{
    if (gpMemoryTracker)
        gpMemoryTracker->removeAllocation((GameObject*)ptr);
    free(ptr);
}

void GameObject::operator delete[](void *ptr)
{
    if (gpMemoryTracker)
        gpMemoryTracker->removeAllocation((GameObject*)ptr);
    free(ptr);
}
