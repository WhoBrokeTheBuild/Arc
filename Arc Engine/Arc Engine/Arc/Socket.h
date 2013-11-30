#pragma once

#ifndef __ARC_SOCKET_H__
#define __ARC_SOCKET_H__

#include "Common.h"
#include "ManagedObject.h"

#include "IPAddress.h"
#include "SocketType.h"
#include "Buffer.h"

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
	class ServerSocket;

	/* A socket representing a connection. Used to send and recieve data
	 */
    class Socket :
        public ManagedObject
    {

		friend class ServerSocket;

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

#endif

		// The address of the destination host
        IPAddress _address;

		// The port to connect to on the destination host
		unsigned int _port;

		// The type of socket (TCP, UDP)
        SocketType _type;

		// Whether the socket is in an error state or not
		bool _error;

#ifdef WINDOWS

		/* Creates a new socket from an existing windows system reference to a socket
		 *
		 * @param socket: The system reference to the socket
		 */
		Socket( SOCKET socket );

#else // LINUX
		
		/* Creates a new socket from an existing linux system reference to a socket
		 *
		 * @param socket: The system reference to the socket
		 */
		Socket( unsigned int socket );

#endif // WINDOWS

    public:

		/* Creates an empty invalid socket
		 */
        Socket( void );

		/* Creates and connects a new socket with the given address, port, and type
		 *
		 * @param addr: The address to connect to
		 * @param port: The port to connect to
		 * @param type: The type of socket to open
		 */
        Socket( IPAddress address, unsigned int port, SocketType type );
		
		/* Creates and connects a new socket with the given address, port, and type
		 *
		 * @param addr: The address to connect to
		 * @param port: The port to connect to
		 * @param type: The type of socket to open
		 */
        Socket( string hostname, unsigned int port, SocketType type );
		
		/* Closes the connection and the socket
		 */
        virtual ~Socket( void );

        virtual inline string toString( void ) const { return "Socket"; }

		/* Creates a new socket of the given type with the given address and port
		 *
		 * @param address: The address to connect to
		 * @param port: The port to connect to
		 * @param type: The type of socket to open (UDP, TCP)
		 * @allocates
		 * @returns: The newly created socket or null on failure
		 */
        bool connectTo( IPAddress address, int port, SocketType type );
		
		/* Creates a new socket of the given type with the given hostname and port
		 *
		 * @param hostname: The hostname to connect to
		 * @param port: The port to connect to
		 * @param type: The type of socket to open (UDP, TCP)
		 * @allocates
		 * @returns: The newly created socket or null on failure
		 */
		inline bool connectTo( string hostname, int port, SocketType type ) { return connectTo(IPAddress::lookup(hostname), port, type); }

		virtual bool hasData( int timeout = 0 );

		/* 
		 * @returns: The type of socket (TCP, UDP)
		 */
        virtual inline SocketType getType( void ) const { return _type; }

		/*
		 * @returns: The address the socket is connected to
		 */
		virtual inline IPAddress getAddress( void ) const { return _address; }

		/* 
		 * @returns: Whether or not the socket is in an error state
		 */
		virtual inline bool hasError( void ) const { return _error; }

		/* Waits for the entire buffer to fill up with packet(s) and returns it as a string
		 *
		 * @param bufferLength: The length of the buffer to wait for
		 * @returns: The string read from the network socket
		 */
		virtual string recvString( unsigned int bufferLength = 2000 );
		
		/* Waits for the entire buffer to fill up with packet(s) and returns it as a Buffer
		 *
		 * @param bufferLength: The length of the buffer to wait for
		 * @returns: The Buffer read from the network socket
		 */
		virtual Buffer recvBuffer( unsigned int bufferLength = 2000 );
		
		/* Reads a single char worth of data on the network socket
		 *
		 * @returns: The char read from the network stream, false on error
		 */
		virtual char recvChar( void );
		
		/* Reads a single boolean worth of data on the network socket
		 *
		 * @returns: The boolean read from the network stream, false on error
		 */
		virtual bool recvBool  ( void );
		
		/* Reads a single short worth of data on the network socket
		 *
		 * @returns: The short read from the network stream, -1 on error
		 */
		virtual short recvShort ( void );
		
		/* Reads a single int worth of data on the network socket
		 *
		 * @returns: The int read from the network stream, -1 on error
		 */
		virtual int recvInt   ( void );
		
		/* Reads a single long worth of data on the network socket
		 *
		 * @returns: The long read from the network stream, -1 on error
		 */
		virtual long recvLong  ( void );
		
		/* Reads a single float worth of data on the network socket
		 *
		 * @returns: The float read from the network stream, -1.0 on error
		 */
		virtual float recvFloat ( void );
		
		/* Reads a single double worth of data on the network socket
		 *
		 * @returns: The double read from the network stream, false on error
		 */
		virtual double recvDouble( void );

		/* Writes a string directly over the network socket with a null terminator
		 *
		 * @param data: The string to send
		 * @returns: The number of bytes written, 0 on error
		 */
		virtual int sendString( string data );
		
		/* Writes a char* buffer directly over the network socket
		 *
		 * @param data: The buffer to send
		 * @returns: The number of bytes written, 0 on error
		 */
		virtual int sendBuffer( char* buffer, int length );
		
		/* Writes a Buffer directly over the network socket
		 *
		 * @param data: The Buffer to send
		 * @returns: The number of bytes written, 0 on error
		 */
		virtual int sendBuffer( const Buffer& buffer );
		
		/* Writes a bool directly over the network socket
		 *
		 * @param data: The bool to send
		 * @returns: The number of bytes written, 0 on error
		 */
		virtual int sendBool  ( bool data );
		
		/* Writes a short directly over the network socket
		 *
		 * @param data: The short to send
		 * @returns: The number of bytes written, 0 on error
		 */
		virtual int sendShort ( short data );
		
		/* Writes a int directly over the network socket
		 *
		 * @param data: The int to send
		 * @returns: The number of bytes written, 0 on error
		 */
		virtual int sendInt   ( int data );
		
		/* Writes a long directly over the network socket
		 *
		 * @param data: The long to send
		 * @returns: The number of bytes written, 0 on error
		 */
		virtual int sendLong  ( long data );
		
		/* Writes a float directly over the network socket
		 *
		 * @param data: The float to send
		 * @returns: The number of bytes written, 0 on error
		 */
		virtual int sendFloat ( float data );
		
		/* Writes a double directly over the network socket
		 *
		 * @param data: The double to send
		 * @returns: The number of bytes written, 0 on error
		 */
		virtual int sendDouble( double data );

    }; // class Socket

} // namespace Arc

#endif // __ARC_SOCKET_H__
