#pragma once

#ifndef __ARC_SERVER_SOCKET_H__
#define __ARC_SERVER_SOCKET_H__

#include "Common.h"
#include "ManagedObject.h"

#include "Socket.h"

namespace Arc
{
	/* A class used to manage a server-side socket. Can check for clients trying to connect and wait for them
	 * to connect.
	 */
	class ServerSocket :
		public ManagedObject
	{
	protected:

		// The port to listen on
		unsigned int _port;

#ifdef WINDOWS
		
		// The windows system reference to the socket
		SOCKET _socket;

#else // LINUX
		
		// The linux system reference to the socket
		int _socket;

#endif // WINDOWS

		/* Closes all sockets in the array of clients and deletes them
		 */
		void cleanup( void );

		/* Prints an error string with WSA information if executing on windows
		 * 
		 * @param msg: The message to display for the error
		 */
		void printError( string msg );

	public:

		/* Creates a new ServerSocket on the given port
		 *
		 * @param port: The port to listen on
		 */
		ServerSocket( unsigned int port );

		/* Calls cleanup() to remove all active clients
		 */
		virtual ~ServerSocket( void );

		virtual inline string toString( void ) const { return "Server Socket"; }

		/* Checks to see if there is currently a client trying to connect
		 *
		 * @returns: Whether or not there is a client currently trying to connect
		 */
		virtual bool isClientAvailable( int timeout = 0 );

		/* Blocks execution until a client connects, once it does it returns a pointer
		 * to it
		 *
		 * @returns: A pointer to the socket that just connected
		 */
		virtual Socket* waitForClient( void );

	}; // class ServerSocket

} // namespace Arc

#endif // __ARC_SERVER_SOCKET_H__