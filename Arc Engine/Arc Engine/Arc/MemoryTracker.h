#pragma once

#ifndef __ARC_MEMORY_TRACKER_H__
#define __ARC_MEMORY_TRACKER_H__

#include "Common.h"
#include "ManagedObject.h"

#include "Map.h"

namespace Arc
{
    struct AllocationRecord
    {

        int
            Num,
            LineNum;

        size_t
            Size;

        string
            Filename;

        AllocationRecord(int num, size_t size, int lineNum, string filename)
            : Num(num),
              LineNum(lineNum),
              Size(size),
              Filename(filename)
        {
        };

    };

    class MemoryTracker
        : public ManagedObject
    {
    private:

        static int
            _sAllocationIndex;

        Map<ManagedObject*, AllocationRecord>
            _allocations;

        MemoryTracker(const MemoryTracker&);
        MemoryTracker& operator=(const MemoryTracker&);

    public:

        MemoryTracker( void );
        virtual ~MemoryTracker( void );

        virtual inline string toString( void ) const { return "Memory Tracker"; }

        void addAllocation   (ManagedObject *ptr, size_t size, int lineNumber, string filename);
        bool removeAllocation(ManagedObject *ptr);

        int  numAllocations( void );

        void printAllocations( void );
        void printAllocations( ostream& stream );

    }; // class MemoryTracker

} // namespace Arc

extern Arc::MemoryTracker* gpMemoryTracker;

#endif // __ARC_MEMORY_TRACKER_H__
