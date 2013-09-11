#include "Socket.h"

Arc::Socket::Socket( void )
{
    _address = IPAddress();
    _type = INVALID_SOCKET_TYPE;
}

void Arc::Socket::init( IPAddress addr, SocketType type )
{
    _address = addr;
    _type    = type;

    _socket = socket(AF_INET, SOCK_STREAM, 0);
}

void Arc::Socket::term( void )
{

}
