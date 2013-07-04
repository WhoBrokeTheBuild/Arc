#include "MemoryTracker.h"

int MemoryTracker::_sAllocationIndex = 0;
MemoryTracker* gpMemoryTracker;

MemoryTracker::MemoryTracker( void )
{
}

MemoryTracker::~MemoryTracker( void )
{

#ifdef DEBUG

    INF(toString(), "Final Allocations");
    printAllocations();

#endif

}

void MemoryTracker::addAllocation( GameObject *ptr, size_t size, int lineNumber, char *filename )
{
    if (_allocations.contains(ptr))
    {
        ERR(toString(), "Element already in map");
        return;
    }

    AllocationRecord rec(_sAllocationIndex, size, lineNumber, string(filename));
    _allocations.add(ptr, rec);

    ++_sAllocationIndex;
}

bool MemoryTracker::removeAllocation( GameObject *ptr )
{
    if (_allocations.size() == 0 || !_allocations.contains(ptr))
        return false;

    _allocations.remove(ptr);
    return true;
}

int MemoryTracker::numAllocations( void )
{
    return _allocations.size();
}

void MemoryTracker::printAllocations( void )
{
    printAllocations(cout);
}

void MemoryTracker::printAllocations( ostream& stream )
{
    stream << "Allocations: \n";

    Map<GameObject*, AllocationRecord>::Iterator it;
    for (it = _allocations.begin(); it != _allocations.end(); ++it)
    {
        stream << "#" << it->second.Num
               << ": (address: #" << it->first << ") "
               << it->first->toString() << "\n";

        stream << "\t In " << basename(it->second.Filename)
               << " On Line " << it->second.LineNum << "\n";
    }
}