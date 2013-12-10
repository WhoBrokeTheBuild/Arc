#pragma once

#ifndef __ARC_NETWORK_SYSTEM_H__
#define __ARC_NETWORK_SYSTEM_H__

#include "Common.h"
#include "SystemComponent.h"

#include "LinkedList.h"
#include "SocketType.h"
#include "Socket.h"
#include "IPAddress.h"

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
	/* A system for managing the underlying networking system and performing
	 * lookups on hostnames.
	 */
    class NetworkSystem :
        public SystemComponent
    {
    protected:

#ifdef WINDOWS

		// The windows reference to the WSA context
        WSADATA _wsa;

#endif // WINDOWS

    public:

		static const SystemComponentType SYS_CMP_TYPE_NETWORK;

		/* Creates a network system and if running on windows, creates a new WSA context
		 */
        NetworkSystem( Program* pProgram );

		/* Cleans up the networking system and if running on windows, closes the WSA context
		 */
        virtual ~NetworkSystem( void );

        virtual inline string toString( void ) const { return "Network System"; }

    }; // class NetworkSystem

} // namespace Arc

#endif // __ARC_NETWORK_SYSTEM_H__
