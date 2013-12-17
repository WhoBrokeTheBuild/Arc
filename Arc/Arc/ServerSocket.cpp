#include "ServerSocket.h"

Arc::ServerSocket::ServerSocket( unsigned int port )
	: _port(port),
	  _error(false),
	  _errorMsg()
{
	_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	if (_socket == INVALID_SOCKET)
	{
		setError("socket() failed");
		cleanup();
		return;
	}

	struct addrinfo *result = nullptr;
	struct addrinfo hints;
	int res;

	memset(&hints, 0, sizeof(hints));

	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;
	hints.ai_flags = AI_PASSIVE;

	stringstream strPort;
	strPort << port;

	res = getaddrinfo(NULL, strPort.str().c_str(), &hints, &result);

	if (res != 0)
	{
		setError("getaddrinfo() failed");
		cleanup();
		freeaddrinfo(result);
		return;
	}

	res = bind(_socket, result->ai_addr, (int)result->ai_addrlen);

	if (res == SOCKET_ERROR)
	{
		setError("bind() failed");
		cleanup();
		freeaddrinfo(result);
		return;
	}

	res = listen(_socket, SOMAXCONN);

	if (res == SOCKET_ERROR)
	{
		setError("listen() failed");
		cleanup();
		freeaddrinfo(result);
		return;
	}

	freeaddrinfo(result);
}

Arc::ServerSocket::~ServerSocket( void )
{
	cleanup();
}

void Arc::ServerSocket::cleanup( void )
{
#ifdef WINDOWS

	closesocket(_socket);

#else // LINUX

	close(_socket);

#endif // WINDOWS
}

void Arc::ServerSocket::setError( string msg )
{
#ifdef WINDOWS

	stringstream ss;
	ss << msg << ", error " << WSAGetLastError();

	msg = ss.str();

#endif

	_errorMsg = msg;
	_error = true;
}

bool Arc::ServerSocket::isClientAvailable( int timeoutMS /*= 0 */ )
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

void Arc::ServerSocket::waitUntilClientAvailable( void )
{
	while ( ! isClientAvailable())
	{
		if (hasError())
			return;
	}
}


Arc::Socket* Arc::ServerSocket::acceptClient( void )
{
#ifdef WINDOWS

	SOCKET client;

#else // LINUX

	int client;

#endif // WINDOWS

	client = accept(_socket, NULL, NULL);

	if (client == INVALID_SOCKET)
	{
		setError("accept() failed");
		cleanup();
		return nullptr;
	}

	Socket* pSocket = New Socket(client);
	return pSocket;
}