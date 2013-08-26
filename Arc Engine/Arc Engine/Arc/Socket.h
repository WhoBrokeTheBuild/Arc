#pragma once

#ifndef __ARC_SOCKET_H__
#define __ARC_SOCKET_H__

#include "Common.h"
#include "ManagedObject.h"

#ifdef WINDOWS

#include <winsock2.h>
#include <Windows.h>
#include <ws2tcpip.h>

#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")

#else // LINUX

#endif // WINDOWS

namespace Arc
{
    class Socket :
        public ManagedObject
    {
    protected:

#ifdef WINDOWS

        SOCKET
            _socket;

#else // LINUX


#endif

    public:

        Socket( void );
        virtual ~Socket( void ) { term(); }

        virtual void init( void );
        virtual void term( void );

    }; // class Socket

} // namespace Arc

#endif // __ARC_SOCKET_H__