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

        SOCKET getWinSocket( void ) const { return _socket; }

#else // LINUX

        int
            _socket;

        int getUnixSocket( void ) const { return _socket; }

#endif

        IPAddress
            _address;

        SocketType
            _type;

    public:

        Socket( void );
        virtual ~Socket( void ) { term(); }

        virtual void init( IPAddress addr, SocketType type );
        virtual void term( void );

        virtual SocketType getType( void ) const { return _type; }

    }; // class Socket

} // namespace Arc

#endif // __ARC_SOCKET_H__
