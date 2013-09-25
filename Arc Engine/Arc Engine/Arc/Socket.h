#pragma once

#ifndef __ARC_SOCKET_H__
#define __ARC_SOCKET_H__

#include "Common.h"
#include "ManagedObject.h"

#include "IPAddress.h"
#include "SocketType.h"

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

		unsigned int
			_port;

        SocketType
            _type;

		bool
			_error;

		// TODO: Hack
		stringstream
			_buffer;

    public:

        Socket( void );
        virtual ~Socket( void ) { term(); }

        virtual void init( IPAddress addr, unsigned int port, SocketType type );
        virtual void term( void );

        virtual inline string toString( void ) const { return "Socket"; }

        virtual SocketType getType( void )   const { return _type; }
		virtual inline bool hasError( void ) const { return _error; }

		virtual string readString( unsigned int bufferLength = 2000 );
		virtual bool   readBool  ( void );
		virtual int    readInt   ( void );
		virtual float  readFloat ( void );
		virtual double readDouble( void );

		virtual int sendString( string data, bool buffer = false );
		virtual int sendBool  ( bool data,   bool buffer = false );
		virtual int sendInt   ( int data,    bool buffer = false );
		virtual int sendFloat ( float data,  bool buffer = false );
		virtual int sendDouble( double data, bool buffer = false );

		virtual inline int bufferString( string data ) { return sendString(data, true); }
		virtual inline int bufferBool  ( bool data )   { return sendBool(data,   true); }
		virtual inline int bufferInt   ( int data )    { return sendInt(data,    true); }
		virtual inline int bufferFloat ( float data )  { return sendFloat(data,  true); }
		virtual inline int bufferDouble( double data ) { return sendDouble(data, true); }

    }; // class Socket

} // namespace Arc

#endif // __ARC_SOCKET_H__
