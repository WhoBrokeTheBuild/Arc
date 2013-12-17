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

#ifdef WINDOWS
		
		// The windows system reference to the socket
		SOCKET _socket;

		/* 
		 * @returns: The windows system reference to the socket
		 */
        SOCKET getWinSocket( void ) const { return _socket; }

#else // LINUX
		
		// The linux system reference to the socket
		int _socket;
		
		/* 
		 * @returns: The linux system reference to the socket
		 */
        int getUnixSocket( void ) const { return _socket; }

#endif // WINDOWS

		// The port to listen on
		unsigned int _port;

		// Indicates whether or not the socket is in an error state
		bool _error;

		// A string describing the current error, if available
		string _errorMsg;

		/* Sets the error flag to true, and sets the error message to the given msg
		 * and appends more information if available
		 *
		 * @param msg: The error message that describes the current error state, or "" if
		 * the socket is not in an error state
		 */
		void setError( string msg );

		/* Safely closes the server socket
		 */
		void cleanup( void );

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
		
		/* 
		 * @returns: Whether or not the socket is in an error state
		 */
		virtual inline bool hasError( void ) const { return _error; }

		/* Gives a string describing the error if available, or an empty string if the socket
		 * is not in an error state.
		 * 
		 * @returns: The string describing the current error, if available, or an empty string
		 */
		virtual inline string getErrorString( void ) { return _errorMsg; }

		/* Checks to see if there is currently a client trying to connect
		 *
		 * @param timeoutMS: The number of milliseconds to wait, or 0 to wait indefinitely 
		 * @returns: Whether or not there is a client currently trying to connect
		 */
		virtual bool isClientAvailable( int timeoutMS = 0 );
		
		/* Blocks execution until a client can connect
		 *
		 * @param timeoutMS: The number of milliseconds to wait, or 0 to wait indefinitely 
		 */
		void waitUntilClientAvailable( void );

		/* Blocks execution until a client connects, once it does it returns a pointer
		 * to it. 
		 *
		 * @returns: A pointer to the socket that just connected, or null on failure
		 */
		virtual Socket* acceptClient( void );

	}; // class ServerSocket

} // namespace Arc

#endif // __ARC_SERVER_SOCKET_H__