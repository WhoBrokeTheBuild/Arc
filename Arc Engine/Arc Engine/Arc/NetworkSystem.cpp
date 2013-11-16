#include "NetworkSystem.h"

Arc::NetworkSystem::NetworkSystem( void )
{
#ifdef WINDOWS

	int res = 0;

	res = WSAStartup(MAKEWORD(2,2), &_wsa);
	if (res != 0)
		ERRORF(toString(), "WSAStartup failed: %d", res);

#endif // WINDOWS
}

Arc::NetworkSystem::~NetworkSystem( void )
{
#ifdef WINDOWS

    WSACleanup();

#endif // WINDOWS
}