#pragma once

#ifndef __ARC_SERVER_SOCKET_H__
#define __ARC_SERVER_SOCKET_H__

#include "Common.h"
#include "ManagedObject.h"

#include "Socket.h"

namespace Arc
{
	class ServerSocket :
		public ManagedObject
	{
	protected:

		ArrayList<Socket*>
			_clients;

		unsigned int
			_port;

#ifdef WINDOWS
		
		SOCKET
			_socket;

#endif // WINDOWS

		void cleanup( void );
		void printError( string msg );

	public:

		ServerSocket( unsigned int port );
		virtual ~ServerSocket( void );

		virtual inline string toString( void ) const { return "Server Socket"; }

		virtual bool isClientAvailable( void );
		virtual Socket* waitForClient( void );
		virtual bool closeClient( Socket* pSocket );

		virtual inline ArrayList<Socket*> getClients( void ) { return _clients; }

	}; // class ServerSocket

} // namespace Arc

#endif // __ARC_SERVER_SOCKET_H__