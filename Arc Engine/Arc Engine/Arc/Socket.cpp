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


}

void Arc::Socket::term( void )
{

}
