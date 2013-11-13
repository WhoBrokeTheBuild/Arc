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

    class Socket :
        public ManagedObject
    {

		friend class ServerSocket;

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

		unsigned int
			_port;

        SocketType
            _type;

		bool
			_error;

#ifdef WINDOWS

		Socket( SOCKET socket );

#else // LINUX

		Socket( unsigned int socket );

#endif // WINDOWS

    public:

        Socket( void );
        virtual ~Socket( void ) { term(); }

        virtual void init( IPAddress addr, unsigned int port, SocketType type );
        virtual void term( void );

        virtual inline string toString( void ) const { return "Socket"; }

        virtual inline SocketType getType   ( void ) const { return _type; }
		virtual inline IPAddress  getAddress( void ) const { return _address; }

		virtual inline bool hasError( void ) const { return _error; }

		virtual string readString( unsigned int bufferLength = 2000 );
		virtual bool   readBool  ( void );
		virtual short  readShort ( void );
		virtual int    readInt   ( void );
		virtual long   readLong  ( void );
		virtual float  readFloat ( void );
		virtual double readDouble( void );

		virtual int sendString( string data );
		virtual int sendBuffer( char* buffer, int length );
		virtual int sendBuffer( const Buffer& buffer );
		virtual int sendBool  ( bool data );
		virtual int sendShort ( short data );
		virtual int sendInt   ( int data );
		virtual int sendLong  ( long data );
		virtual int sendFloat ( float data );
		virtual int sendDouble( double data );

		virtual inline int bufferString( string data, char* buffer, int offset );
		virtual inline int bufferBool  ( bool data, char* buffer, int offset );
		virtual inline int bufferShort ( short data, char* buffer, int offset );
		virtual inline int bufferInt   ( int data, char* buffer, int offset );
		virtual inline int bufferLong  ( long data, char* buffer, int offset );
		virtual inline int bufferFloat ( float data, char* buffer, int offset );
		virtual inline int bufferDouble( double data, char* buffer, int offset );

    }; // class Socket

} // namespace Arc

#endif // __ARC_SOCKET_H__
