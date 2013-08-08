#include "ManagedObject.h"
#include "MemoryTracker.h"

void *Arc::ManagedObject::operator new( size_t size )
{
    return malloc(size);
}
void *Arc::ManagedObject::operator new[]( size_t size )
{
    return malloc(size);
}

void *Arc::ManagedObject::operator new( size_t size, int lineNumber, const char *filename )
{
    void* ptr = ::operator new(size);
    if (gpMemoryTracker)
        gpMemoryTracker->addAllocation((ManagedObject*)ptr, size, lineNumber, string(filename));
    return ptr;
}

void *Arc::ManagedObject::operator new[]( size_t size, int lineNumber, const char *filename )
{
    void* ptr = ::operator new(size);
    if (gpMemoryTracker)
        gpMemoryTracker->addAllocation((ManagedObject*)ptr, size, lineNumber, string(filename));
    return ptr;
}

void Arc::ManagedObject::operator delete( void *ptr, int lineNumber, const char *filename )
{
    ::operator delete(ptr);
    if (gpMemoryTracker)
        gpMemoryTracker->removeAllocation((ManagedObject*)ptr);
    free(ptr);
}

void Arc::ManagedObject::operator delete[]( void *ptr, int lineNumber, const char *filename )
{
    ::operator delete(ptr);
    if (gpMemoryTracker)
        gpMemoryTracker->removeAllocation((ManagedObject*)ptr);
    free(ptr);
}

void Arc::ManagedObject::operator delete( void *ptr )
{
    if (gpMemoryTracker)
        gpMemoryTracker->removeAllocation((ManagedObject*)ptr);
    free(ptr);
}

void Arc::ManagedObject::operator delete[]( void *ptr )
{
    if (gpMemoryTracker)
        gpMemoryTracker->removeAllocation((ManagedObject*)ptr);
    free(ptr);
}