#include "NetworkSystem.h"

Arc::NetworkSystem::NetworkSystem( void )
{

}

void Arc::NetworkSystem::init( void )
{

#ifdef WINDOWS

    int res = 0;

    res = WSAStartup(MAKEWORD(2,2), &_wsa);
    if (res != 0)
        ERRORF(toString(), "WSAStartup failed: %d", res);

#endif // WINDOWS

}

void Arc::NetworkSystem::term( void )
{

#ifdef WINDOWS

    WSACleanup();

#endif // WINDOWS

}

Arc::Socket* Arc::NetworkSystem::connect( string hostname, int port, SocketType type )
{
	return connect(lookup(hostname), port, type);
}

Arc::Socket* Arc::NetworkSystem::connect( IPAddress addr, int port, SocketType type )
{
	Socket* sock = New Socket();
	sock->init(addr, port, type);
	return sock;
}

Arc::IPAddress Arc::NetworkSystem::lookup( string hostname )
{
	hostent* host = gethostbyname(hostname.c_str());

	if ( ! host)
		return IPAddress::ZERO;

	return IPAddress(host->h_addr_list[0][0],
					 host->h_addr_list[0][1],
					 host->h_addr_list[0][2], 
					 host->h_addr_list[0][3]);
}
