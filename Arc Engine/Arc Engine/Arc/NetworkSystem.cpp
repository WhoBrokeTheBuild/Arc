#include "NetworkSystem.h"

const Arc::SystemComponentType Arc::NetworkSystem::SYS_CMP_TYPE_NETWORK = "network";

Arc::NetworkSystem::NetworkSystem( Program* pProgram )
	: SystemComponent(pProgram)
{
	INFO(toString(), "Initializing");

	addType(SYS_CMP_TYPE_NETWORK);

#ifdef WINDOWS

	int res = 0;

	res = WSAStartup(MAKEWORD(2,2), &_wsa);
	if (res != 0)
		ERRORF(toString(), "WSAStartup failed: %d", res);

#endif // WINDOWS

	INFO(toString(), "Complete");
}

Arc::NetworkSystem::~NetworkSystem( void )
{
	INFO(toString(), "Terminating");

#ifdef WINDOWS

    WSACleanup();

#endif // WINDOWS

	INFO(toString(), "Complete");
}