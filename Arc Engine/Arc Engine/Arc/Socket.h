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

		virtual string recvString( unsigned int maxLength = 2000 );
		virtual Buffer recvBuffer( unsigned int bufferLength = 2000 );
		virtual bool   recvBool  ( void );
		virtual short  recvShort ( void );
		virtual int    recvInt   ( void );
		virtual long   recvLong  ( void );
		virtual float  recvFloat ( void );
		virtual double recvDouble( void );

		virtual int sendString( string data );
		virtual int sendBuffer( char* buffer, int length );
		virtual int sendBuffer( const Buffer& buffer );
		virtual int sendBool  ( bool data );
		virtual int sendShort ( short data );
		virtual int sendInt   ( int data );
		virtual int sendLong  ( long data );
		virtual int sendFloat ( float data );
		virtual int sendDouble( double data );

    }; // class Socket

} // namespace Arc

#endif // __ARC_SOCKET_H__
