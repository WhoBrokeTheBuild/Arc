#include "MemoryTracker.h"

int Arc::MemoryTracker::_sAllocationIndex = 0;
Arc::MemoryTracker*     gpMemoryTracker   = nullptr;

Arc::MemoryTracker::MemoryTracker( void )
{
    _sAllocationIndex = 0;
    _allocations      = Map<ManagedObject*, AllocationRecord>();
}

void Arc::MemoryTracker::addAllocation( ManagedObject *ptr, size_t size, int lineNumber, string filename )
{
    if (_allocations.containsKey(ptr))
    {
        ERROR(toString(), "Element already in map");
        return;
    }

    AllocationRecord rec(_sAllocationIndex, size, lineNumber, filename);
    _allocations.add(ptr, rec);

    ++_sAllocationIndex;
}

bool Arc::MemoryTracker::removeAllocation( ManagedObject *ptr )
{
    if (_allocations.getSize() == 0 || !_allocations.containsKey(ptr))
        return false;

    _allocations.removeKey(ptr);
    return true;
}

int Arc::MemoryTracker::numAllocations( void )
{
    return _allocations.getSize();
}

void Arc::MemoryTracker::printAllocations( void )
{
    printAllocations(cout);
}

void Arc::MemoryTracker::printAllocations( ostream& stream )
{
    stream << "Allocations: \n";

    Map<ManagedObject*, AllocationRecord>::Iterator it;
    for (it = _allocations.begin(); it != _allocations.end(); ++it)
    {
        stream << "#" << it->second.Num
               << ": (address: #" << it->first << ") "
               << it->first->toString() << "\n";

        stream << "\t In " << basename(it->second.Filename)
               << " On Line " << it->second.LineNum << "\n";
    }
}
