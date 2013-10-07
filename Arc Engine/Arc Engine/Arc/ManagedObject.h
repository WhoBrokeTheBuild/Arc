#pragma once

#ifndef __ARC_MANAGED_OBJECT_H__
#define __ARC_MANAGED_OBJECT_H__

#include <string>
#include <sstream>
#include <iostream>

using std::string;
using std::ostream;

namespace Arc
{
	/** Base object for all memory managed objects
	  */
    class ManagedObject
    {
    public:

		// Universal function to turn an object into a string, used to identify objects when debugging
        virtual string toString( void ) const = 0;

		// Helper function to allow outputting objects through file streams using the toString() function
        inline friend ostream& operator<<( ostream& os, const ManagedObject& go )
        {
            os << go.toString();
            return os;
        }

		// Normal new operator
        void* operator new  ( size_t size );
        void* operator new[]( size_t size );

		// Operator for placement new, takes in the filename and line number 
        void* operator new  ( size_t pSize, int pLineNumber, const char *pFilename );
        void* operator new[]( size_t pSize, int pLineNumber, const char *pFilename );

		// Normal delete operator
        void operator delete  ( void *ptr);
        void operator delete[]( void *ptr);

		// Required because of the placement new operator, should not be used
        void operator delete  ( void *pPtr, int pLineNumber, const char *pFilename );
        void operator delete[]( void *pPtr, int pLineNumber, const char *pFilename );

#ifdef DEBUG

// Used to pass the filename and line number into the placement new operator
#define New new(__LINE__, __FILE__)

#else

// When not debugging, use the normal new operator
#define New new

#endif

    }; // class ManagedObject

} // namespace Arc

#endif // __ARC_MANAGED_OBJECT_H__
