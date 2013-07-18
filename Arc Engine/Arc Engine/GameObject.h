#pragma once

#ifndef __ARC_GAME_OBJECT_H__
#define __ARC_GAME_OBJECT_H__

#include <string>
#include <sstream>
#include <iostream>

using namespace std;

namespace Arc
{
    class GameObject
    {
    private:

    public:

        virtual ~GameObject( void ) { }

        virtual string toString( void ) const = 0;

        friend ostream& operator<<( ostream& os, const GameObject& go );

        void* operator new  (size_t size);
        void* operator new[](size_t size);

        void* operator new  (size_t pSize, int pLineNumber, const char *pFilename);
        void* operator new[](size_t pSize, int pLineNumber, const char *pFilename);

        void operator delete  (void *ptr);
        void operator delete[](void *ptr);

        void operator delete  (void *pPtr, int pLineNumber, const char *pFilename);
        void operator delete[](void *pPtr, int pLineNumber, const char *pFilename);

        #ifdef DEBUG

        #define New new(__LINE__, __ARC_FILE__)

        #else

        #define New new

        #endif

    };
}

#endif
