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
	  _error(false),
	  _errorMsg()
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
		setError("getpeername() failed");
		cleanup();
	}

	_address = IPAddress(inet_ntoa(name.sin_addr));
	_port = name.sin_port;
	_type = SOCKET_TYPE_TCP; // TODO: Get actual socket type when UDP is implemented
}

Arc::Socket::Socket( IPAddress address, unsigned int port, SocketType type )
	: _socket(INVALID_SOCKET),
	  _error(false),
	  _errorMsg()
{
	connectTo(address, port, type);
}

Arc::Socket::Socket( string hostname, unsigned int port, SocketType type )
	: _socket(INVALID_SOCKET),
	  _error(false),
	  _errorMsg()
{
	connectTo(hostname, port, type);
}

Arc::Socket::~Socket( void )
{
	cleanup();
}

void Arc::Socket::cleanup( void )
{
#ifdef WINDOWS

	closesocket(_socket);

#else // LINUX

	close(_socket);

#endif // WINDOWS
}

void Arc::Socket::setError( string msg )
{
#ifdef WINDOWS

	stringstream ss;
	ss << msg << ", error " << WSAGetLastError();

	msg = ss.str();

#endif

	_errorMsg = msg;
}

bool Arc::Socket::connectTo( IPAddress address, int port, SocketType type )
{
	_address = address;
	_port = port;
	_type = type;

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

#ifdef WINDOWS

	saddr.sin_addr.S_un.S_un_b.s_b1 = rawAddr[0];
	saddr.sin_addr.S_un.S_un_b.s_b2 = rawAddr[1];
	saddr.sin_addr.S_un.S_un_b.s_b3 = rawAddr[2];
	saddr.sin_addr.S_un.S_un_b.s_b4 = rawAddr[3];

#else // LINUX

	uint8_t* addr = (uint8_t*)saddr.sin_addr.s_addr;
	addr[0] = rawAddr[0];
	addr[1] = rawAddr[1];
	addr[2] = rawAddr[2];
	addr[3] = rawAddr[3];

#endif // WINDOWS

	int result = connect(_socket, (sockaddr*)&saddr, sizeof saddr);
	if (result == SOCKET_ERROR)
	{
		setError("connect() failed");
		cleanup();
		return false;
	}

	return true;
}

bool Arc::Socket::hasData( int timeoutMS /*= 0 */ )
{
	fd_set fds;
	FD_ZERO(&fds);
	FD_SET(_socket, &fds);

	int timeoutSec = timeoutMS / 1000;
	int timeoutUS = (timeoutMS % 1000) * 1000;

	timeval tv;
	tv.tv_sec = timeoutSec;
	tv.tv_usec = timeoutUS;

	int result = select(_socket + 1, &fds, 0, 0, &tv);

	if (result < 0)
	{
		setError("select() failed");
		cleanup();
		return false;
	}

	return (result == 1);
}


string Arc::Socket::recvString( unsigned int bufferLength /*= 2000 */ )
{
	char* buffer = new char[bufferLength + 1];

	int bytes = recv(_socket, buffer, bufferLength, 0);

	if (bytes == 0)
	{
		setError("recv() failed");
		cleanup();
		return "";
	}

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
	buf.setEndOfUsed(bufferLength);

	if (bytes == 0)
	{
		setError("recv() failed");
		cleanup();
		return Buffer();
	}

	return buf;
}

char Arc::Socket::recvChar( void )
{
	char buffer;

	int bytes = recv(_socket, &buffer, 1, 0);

	if (bytes == 0)
	{
		setError("recv() failed");
		cleanup();
		return '\0';
	}

	return buffer;
}

bool Arc::Socket::recvBool( void )
{
	char buffer;

	int bytes = recv(_socket, &buffer, 1, 0);

	if (bytes == 0)
	{
		setError("recv() failed");
		cleanup();
		return false;
	}

	bool val;
	memcpy(&val, &buffer, sizeof(bool));

	return val;
}

short Arc::Socket::recvShort( void )
{
	char buffer[sizeof(short)];

	int bytes = recv(_socket, buffer, 4, 0);

	if (bytes == 0)
	{
		setError("recv() failed");
		cleanup();
		return -1;
	}

	short num;
	memcpy(&num, buffer, sizeof(short));

	return num;
}

int Arc::Socket::recvInt( void )
{
	char buffer[sizeof(int)];

	int bytes = recv(_socket, buffer, 4, 0);

	if (bytes == 0)
	{
		setError("recv() failed");
		cleanup();
		return -1;
	}

	int num;
	memcpy(&num, buffer, sizeof(int));

	return num;
}

long Arc::Socket::recvLong( void )
{
	char buffer[sizeof(long)];

	int bytes = recv(_socket, buffer, 4, 0);

	if (bytes == 0)
	{
		setError("recv() failed");
		cleanup();
		return -1L;
	}

	long num;
	memcpy(&num, buffer, sizeof(long));

	return num;
}

float Arc::Socket::recvFloat( void )
{
	char buffer[sizeof(float)];

	int bytes = recv(_socket, buffer, 4, 0);

	if (bytes == 0)
	{
		setError("recv() failed");
		cleanup();
		return -1.0f;
	}

	float num;
	memcpy(&num, buffer, sizeof(float));

	return num;
}

double Arc::Socket::recvDouble( void )
{
	char buffer[sizeof(double)];

	int bytes = recv(_socket, buffer, 4, 0);

	if (bytes == 0)
	{
		setError("recv() failed");
		cleanup();
		return -1.0;
	}

	double num;
	memcpy(&num, buffer, sizeof(double));

	return num;
}

int Arc::Socket::sendString( string data )
{
	int bytes = send(_socket, data.c_str(), data.length() + 1, 0);

	if (bytes == 0)
	{
		setError("send() failed");
		cleanup();
	}

	return bytes;
}

int Arc::Socket::sendBuffer( char* buffer, int length )
{
	if (length == 0)
		return 0;

	int bytes = send(_socket, buffer, length, 0);

	if (bytes == 0)
	{
		setError("send() failed");
		cleanup();
	}

	return bytes;
}

int Arc::Socket::sendBuffer( const Buffer& buffer )
{
	if (buffer.getFullSize() == 0)
		return 0;

	int bytes = send(_socket, buffer.getRawBuffer(), buffer.getFullSize(), 0);

	if (bytes == 0)
	{
		setError("send() failed");
		cleanup();
	}

	return bytes;
}

int Arc::Socket::sendBool( bool data )
{
	int bytes = send(_socket, (char*)&data, sizeof data, 0);

	if (bytes == 0)
	{
		setError("send() failed");
		cleanup();
	}

	return bytes;
}

int Arc::Socket::sendShort( short data )
{
	int bytes = send(_socket, (char*)&data, sizeof data, 0);

	if (bytes == 0)
	{
		setError("send() failed");
		cleanup();
	}

	return bytes;
}

int Arc::Socket::sendInt( int data )
{
	int bytes = send(_socket, (char*)&data, sizeof data, 0);

	if (bytes == 0)
	{
		setError("send() failed");
		cleanup();
	}

	return bytes;
}

int Arc::Socket::sendLong( long data )
{
	int bytes = send(_socket, (char*)&data, sizeof data, 0);

	if (bytes == 0)
	{
		setError("send() failed");
		cleanup();
	}

	return bytes;
}

int Arc::Socket::sendFloat( float data )
{
	int bytes = send(_socket, (char*)&data, sizeof data, 0);

	if (bytes == 0)
	{
		setError("send() failed");
		cleanup();
	}

	return bytes;
}

int Arc::Socket::sendDouble( double data )
{
	int bytes = send(_socket, (char*)&data, sizeof data, 0);

	if (bytes == 0)
	{
		setError("send() failed");
		cleanup();
	}

	return bytes;
}
