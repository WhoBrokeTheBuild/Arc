#include "ManagedObject.h"
#include "MemoryTracker.h"

void *Arc::ManagedObject::operator new( size_t size )
{
	// Allocate memory normally 
    return malloc(size);
}
void *Arc::ManagedObject::operator new[]( size_t size )
{
	// Allocate memory normally 
    return malloc(size);
}

void *Arc::ManagedObject::operator new( size_t size, int lineNumber, const char *filename )
{
	// Call base operator
    void* ptr = ::operator new(size);

	// Record allocation in memory tracker
    if (gpMemoryTracker)
        gpMemoryTracker->addAllocation((ManagedObject*)ptr, size, lineNumber, string(filename));

    return ptr;
}

void *Arc::ManagedObject::operator new[]( size_t size, int lineNumber, const char *filename )
{
	// Call base operator
    void* ptr = ::operator new(size);

	// Record allocation in memory tracker
    if (gpMemoryTracker)
        gpMemoryTracker->addAllocation((ManagedObject*)ptr, size, lineNumber, string(filename));

    return ptr;
}

void Arc::ManagedObject::operator delete( void *ptr, int lineNumber, const char *filename )
{
    ::operator delete(ptr);
}

void Arc::ManagedObject::operator delete[]( void *ptr, int lineNumber, const char *filename )
{
    ::operator delete(ptr);
}

void Arc::ManagedObject::operator delete( void *ptr )
{
	// Remove the allocation record if it exists
    if (gpMemoryTracker)
        gpMemoryTracker->removeAllocation((ManagedObject*)ptr);

	// Free memory normally 
    free(ptr);
}

void Arc::ManagedObject::operator delete[]( void *ptr )
{
	// Remove the allocation record if it exists
    if (gpMemoryTracker)
		gpMemoryTracker->removeAllocation((ManagedObject*)ptr);

	// Free memory normally 
    free(ptr);
}