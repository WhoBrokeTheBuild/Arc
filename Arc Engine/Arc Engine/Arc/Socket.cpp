#include "Socket.h"
#include "ServerSocket.h"

#ifdef WINDOWS

Arc::Socket::Socket( SOCKET socket )

#else // LINUX

Arc::Socket::Socket( unsigned int socket )

#endif // WINDOWS

	: _address(),
	  _port(), 
	  _type(INVALID_SOCKET_TYPE),
	  _socket(socket),
	  _error(false)
{
	char buf[INET_ADDRSTRLEN] = "";
	struct sockaddr_in name;
	socklen_t len = sizeof(name);
	int res;

	res = getpeername(socket, (struct sockaddr *)&name, &len);

	if (res == 0)
	{
		inet_ntop(AF_INET, &name.sin_addr, buf, sizeof buf);
	}
	else
	{
		ERRORF(toString(), "getpeername() failed, error %i", res);
	}

	_address = IPAddress(inet_ntoa(name.sin_addr));
	_port = name.sin_port;
	_type = SOCKET_TYPE_TCP; // TODO: Get actual socket type when UDP is implemented
}

Arc::Socket::Socket( void )
	: _address(),
	  _port(), 
	  _type(INVALID_SOCKET_TYPE),
	  _socket(INVALID_SOCKET),
	  _error(false)
{
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

	uint8_t* rawAddr = _address.getRawData();

	saddr.sin_addr.S_un.S_un_b.s_b1 = rawAddr[0];
	saddr.sin_addr.S_un.S_un_b.s_b2 = rawAddr[1];
	saddr.sin_addr.S_un.S_un_b.s_b3 = rawAddr[2];
	saddr.sin_addr.S_un.S_un_b.s_b4 = rawAddr[3];

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

int Arc::Socket::sendString( string data )
{
	return send(_socket, data.c_str(), data.length(), 0);
}

int Arc::Socket::sendBuffer( char* buffer, int length )
{
	return send(_socket, buffer, length, 0);
}

int Arc::Socket::sendBuffer( const Buffer& buffer )
{
	return send(_socket, buffer.getRawBuffer(), buffer.getFullSize(), 0);
}

int Arc::Socket::sendBool( bool data )
{
	return send(_socket, (char*)&data, sizeof data, 0);
}

int Arc::Socket::sendShort( short data )
{
	return send(_socket, (char*)&data, sizeof data, 0);
}

int Arc::Socket::sendInt( int data )
{
	return send(_socket, (char*)&data, sizeof data, 0);
}

int Arc::Socket::sendLong( long data )
{
	return send(_socket, (char*)&data, sizeof data, 0);
}

int Arc::Socket::sendFloat( float data )
{
	return send(_socket, (char*)&data, sizeof data, 0);
}

int Arc::Socket::sendDouble( double data )
{
	return send(_socket, (char*)&data, sizeof data, 0);
}

string Arc::Socket::recvString( unsigned int bufferLength /*= 2000 */ )
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

Arc::Buffer Arc::Socket::recvBuffer( unsigned int bufferLength /*= 2000 */ )
{
	Buffer buf;
	buf.resize(bufferLength);
	
	int bytes = recv(_socket, buf.getRawBuffer(), bufferLength, 0);

	if (bytes == -1)
		return Buffer();

	return buf;
}

bool Arc::Socket::recvBool( void )
{
	char buffer;

	int bytes = recv(_socket, &buffer, 1, 0);

	if (bytes == -1)
		return false;

	bool val;
	memcpy(&val, &buffer, sizeof(bool));

	return val;
}

short Arc::Socket::recvShort( void )
{
	char buffer[sizeof(short)];

	int bytes = recv(_socket, buffer, 4, 0);

	if (bytes == -1)
		return false;

	short num;
	memcpy(&num, buffer, sizeof(short));

	return num;
}

int Arc::Socket::recvInt( void )
{
	char buffer[sizeof(int)];

	int bytes = recv(_socket, buffer, 4, 0);

	if (bytes == -1)
		return false;

	int num;
	memcpy(&num, buffer, sizeof(int));

	return num;
}

long Arc::Socket::recvLong( void )
{
	char buffer[sizeof(long)];

	int bytes = recv(_socket, buffer, 4, 0);

	if (bytes == -1)
		return false;

	long num;
	memcpy(&num, buffer, sizeof(long));

	return num;
}

float Arc::Socket::recvFloat( void )
{
	char buffer[sizeof(float)];

	int bytes = recv(_socket, buffer, 4, 0);

	if (bytes == -1)
		return false;

	float num;
	memcpy(&num, buffer, sizeof(float));

	return num;
}

double Arc::Socket::recvDouble( void )
{
	char buffer[sizeof(double)];

	int bytes = recv(_socket, buffer, 4, 0);

	if (bytes == -1)
		return false;

	double num;
	memcpy(&num, buffer, sizeof(double));

	return num;
}
