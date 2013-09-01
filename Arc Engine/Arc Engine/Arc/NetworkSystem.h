#pragma once

#ifndef __ARC_NETWORK_SYSTEM_H__
#define __ARC_NETWORK_SYSTEM_H__

#include "Common.h"
#include "ManagedObject.h"

#include "LinkedList.h"

#ifdef WINDOWS

#include <winsock2.h>
#include <Windows.h>
#include <ws2tcpip.h>

#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")

#else // LINUX

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#endif // WINDOWS

namespace Arc
{
    class Socket;
    class IPAddress;
    class SocketType;

    class NetworkSystem :
        public ManagedObject
    {
    protected:

        LinkedList<Socket*>
            _socketList;

#ifdef WINDOWS

        WSADATA
            _wsa;

#endif // WINDOWS

    public:

        NetworkSystem( void );
        virtual ~NetworkSystem( void ) { term(); }

        virtual void init( void );
        virtual void term( void );

        virtual inline string toString( void ) const { return "Network System"; }

        virtual Socket connect( string hostname, SocketType type );
        virtual Socket connect( IPAddress addr, SocketType type );

    }; // class NetworkSystem

} // namespace Arc

#endif // __ARC_NETWORK_SYSTEM_H__
