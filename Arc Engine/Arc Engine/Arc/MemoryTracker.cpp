#include "MemoryTracker.h"

int Arc::MemoryTracker::_sAllocationIndex = 0;
Arc::MemoryTracker*     gpMemoryTracker   = nullptr;

Arc::MemoryTracker::MemoryTracker( void )
{
    _sAllocationIndex = 0;
    _allocations      = Map<GameObject*, AllocationRecord>();
}

Arc::MemoryTracker::~MemoryTracker( void )
{
#ifdef DEBUG

    INFO(toString(), "Final Allocations");
    printAllocations();

#endif // DEBUG
}

void Arc::MemoryTracker::addAllocation( GameObject *ptr, size_t size, int lineNumber, string filename )
{
    if (_allocations.contains(ptr))
    {
        ERROR(toString(), "Element already in map");
        return;
    }

    AllocationRecord rec(_sAllocationIndex, size, lineNumber, filename);
    _allocations.add(ptr, rec);

    ++_sAllocationIndex;
}

bool Arc::MemoryTracker::removeAllocation( GameObject *ptr )
{
    if (_allocations.size() == 0 || !_allocations.contains(ptr))
        return false;

    _allocations.remove(ptr);
    return true;
}

int Arc::MemoryTracker::numAllocations( void )
{
    return _allocations.size();
}

void Arc::MemoryTracker::printAllocations( void )
{
    printAllocations(cout);
}

void Arc::MemoryTracker::printAllocations( ostream& stream )
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
