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

}

Arc::Socket Arc::NetworkSystem::connect( string hostname, SocketType type )
{
    return Socket();
}

Arc::Socket Arc::NetworkSystem::connect( IPAddress addr, SocketType type )
{
    return Socket();
}
