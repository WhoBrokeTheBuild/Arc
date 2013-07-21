#pragma once

#ifndef __ARC_MEMORY_TRACKER_H__
#define __ARC_MEMORY_TRACKER_H__

#include "Common.h"
#include "GameObject.h"

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
        : public GameObject
    {
    private:

        static int
            _sAllocationIndex;

        Map<GameObject*, AllocationRecord>
            _allocations;

        MemoryTracker(const MemoryTracker&);
        MemoryTracker& operator=(const MemoryTracker&);

    public:

        MemoryTracker( void );
        virtual ~MemoryTracker( void );

        virtual string toString( void ) const { return "Memory Tracker"; }

        void addAllocation   (GameObject *ptr, size_t size, int lineNumber, string filename);
        bool removeAllocation(GameObject *ptr);

        int  numAllocations( void );

        void printAllocations( void );
        void printAllocations( ostream& stream );

    }; // class MemoryTracker

} // namespace Arc

extern Arc::MemoryTracker* gpMemoryTracker;

#endif // __ARC_MEMORY_TRACKER_H__
