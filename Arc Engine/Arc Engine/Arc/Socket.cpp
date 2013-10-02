#include "Socket.h"

Arc::Socket::Socket( void )
{
    _address = IPAddress();
	_port    = 0;
    _type    = INVALID_SOCKET_TYPE;
	_socket  = INVALID_SOCKET;
	_error   = false;
}

void Arc::Socket::init( IPAddress addr, unsigned int port, SocketType type )
{
    _address = addr;
	_port    = port;
	_type    = type;
	_error   = false;

	if (type == SOCKET_TYPE_TCP)
	{
		_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	}
	else if (type == SOCKET_TYPE_UDP)
	{
		_socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	}

	sockaddr_in saddr;
	saddr.sin_family = AF_INET;
	saddr.sin_port   = htons(_port);

	saddr.sin_addr.S_un.S_un_b.s_b1 = _address.getRawData()[0];
	saddr.sin_addr.S_un.S_un_b.s_b2 = _address.getRawData()[1];
	saddr.sin_addr.S_un.S_un_b.s_b3 = _address.getRawData()[2];
	saddr.sin_addr.S_un.S_un_b.s_b4 = _address.getRawData()[3];

	int result = connect(_socket, (sockaddr*)&saddr, sizeof saddr);
	if (result == SOCKET_ERROR)
	{
		_error = true;
		return;
	}
}

void Arc::Socket::term( void )
{

#ifdef WINDOWS

	closesocket(_socket);

#else // LINUX

	close(_socket);

#endif // WINDOWS

}

int Arc::Socket::sendString( string data, bool buffer /*= false */ )
{
	if (buffer)
	{
		_buffer << data;
		return data.length() + 1;
	}
	else
	{
		return send(_socket, data.c_str(), data.length(), 0);
	}
}

int Arc::Socket::sendBool( bool data, bool buffer /*= false */ )
{
	if (buffer)
	{
		_buffer << (char*)&data;
		return sizeof data;
	}
	else
	{
		return send(_socket, (char*)&data, sizeof data, 0);
	}
}

int Arc::Socket::sendInt( int data, bool buffer /*= false */ )
{
	if (buffer)
	{
		_buffer << (char*)&data;
		return sizeof data;
	}
	else
	{
		return send(_socket, (char*)&data, sizeof data, 0);
	}
}

int Arc::Socket::sendFloat( float data, bool buffer /*= false */ )
{
	if (buffer)
	{
		_buffer << (char*)&data;
		return sizeof data;
	}
	else
	{
		return send(_socket, (char*)&data, sizeof data, 0);
	}
}

int Arc::Socket::sendDouble( double data, bool buffer /*= false */ )
{
	if (buffer)
	{
		_buffer << (char*)&data;
		return sizeof data;
	}
	else
	{
		return send(_socket, (char*)&data, sizeof data, 0);
	}
}

string Arc::Socket::readString( unsigned int bufferLength /*= 2000 */ )
{
	char* buffer = new char[bufferLength + 1];

	int bytes = recv(_socket, buffer, bufferLength, 0);

	if (bytes == -1)
		return "";

	buffer[bytes] = '\0';
	string data = string(buffer);

	delete[] buffer;

	return data;
}

bool Arc::Socket::readBool( void )
{
	return false;
}

int Arc::Socket::readInt( void )
{
	return 0;
}

float Arc::Socket::readFloat( void )
{
	return 0.0f;
}

double Arc::Socket::readDouble( void )
{
	return 0.0;
}
