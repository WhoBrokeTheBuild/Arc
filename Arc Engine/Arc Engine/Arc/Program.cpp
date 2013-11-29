#include "Program.h"

Arc::Program* Arc::Program::_pInstance = nullptr;

Arc::Program::Program( void )
	: _systems()
{
    INFO(toString(), "Initializing");

	_pInstance = this;

    initRandom();

    INFO(toString(), "Complete");
}

Arc::Program::~Program( void )
{
    INFO(toString(), "Terminating");

	termNetworkSystem();
	termScriptingSystem();

    INFO(toString(), "Complete");
}

void Arc::Program::initScriptingSystem( void )
{
	delete getSystemOfType<ScriptingSystem>(ScriptingSystem::SYS_CMP_TYPE_SCRIPTING);
    _systems.add(New ScriptingSystem(this));
}

void Arc::Program::initNetworkSystem( void )
{
	delete getSystemOfType<NetworkSystem>(NetworkSystem::SYS_CMP_TYPE_NETWORK);
    _systems.add(New NetworkSystem(this));
}

void Arc::Program::termScriptingSystem( void )
{
	ScriptingSystem* pSys = getSystemOfType<ScriptingSystem>(ScriptingSystem::SYS_CMP_TYPE_SCRIPTING);
	delete pSys;
	_systems.remove(pSys);
}

void Arc::Program::termNetworkSystem( void )
{
	NetworkSystem* pSys = getSystemOfType<NetworkSystem>(NetworkSystem::SYS_CMP_TYPE_NETWORK);
	delete pSys;
	_systems.remove(pSys);
}
