#pragma once

#ifndef __ARC_GAME_OBJECT_H__
#define __ARC_GAME_OBJECT_H__

#include <string>
#include <sstream>
#include <iostream>

using std::string;
using std::ostream;

namespace Arc
{
    class GameObject
    {
    public:

        virtual ~GameObject( void ) { }

        virtual string toString( void ) const = 0;

        friend ostream& operator<<( ostream& os, const GameObject& go )
        {
            os << go.toString();
            return os;
        }

        void* operator new  ( size_t size );
        void* operator new[]( size_t size );
                              
        void* operator new  ( size_t pSize, int pLineNumber, const char *pFilename );
        void* operator new[]( size_t pSize, int pLineNumber, const char *pFilename );

        void operator delete  ( void *ptr);
        void operator delete[]( void *ptr);
                                
        void operator delete  ( void *pPtr, int pLineNumber, const char *pFilename );
        void operator delete[]( void *pPtr, int pLineNumber, const char *pFilename );

#ifdef DEBUG

#define New new(__LINE__, __FILE__)

#else

#define New new

#endif

    }; // class GameObject

} // namespace Arc

#endif // __ARC_GAME_OBJECT_H__
