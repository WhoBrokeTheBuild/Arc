#include "Program.h"

Arc::Program* Arc::Program::_pInstance = nullptr;

const Arc::EventType Arc::Program::EVENT_NETWORK_SYSTEM_INITIALIZED   = "program.networkSystemInitialzed";
const Arc::EventType Arc::Program::EVENT_NETWORK_SYSTEM_TERMINATED    = "program.networkSystemTerminated";
const Arc::EventType Arc::Program::EVENT_SCRIPTING_SYSTEM_INITIALIZED = "program.scriptingSystemInitialzed";
const Arc::EventType Arc::Program::EVENT_SCRIPTING_SYSTEM_TERMINATED  = "program.scriptingSystemTerminated";

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
	termScriptingSystem();
    _systems.add(New ScriptingSystem(this));
	dispatchEvent(Event(EVENT_SCRIPTING_SYSTEM_INITIALIZED));
}

void Arc::Program::initNetworkSystem( void )
{
	termNetworkSystem();
	_systems.add(New NetworkSystem(this));
	dispatchEvent(Event(EVENT_NETWORK_SYSTEM_INITIALIZED));
}

void Arc::Program::termScriptingSystem( void )
{
	ScriptingSystem* pSys = getSystemOfType<ScriptingSystem>(ScriptingSystem::SYS_CMP_TYPE_SCRIPTING);

	if (pSys != nullptr)
	{
		delete pSys;
		_systems.remove(pSys);
		dispatchEvent(Event(EVENT_SCRIPTING_SYSTEM_TERMINATED));
	}
}

void Arc::Program::termNetworkSystem( void )
{
	NetworkSystem* pSys = getSystemOfType<NetworkSystem>(NetworkSystem::SYS_CMP_TYPE_NETWORK);

	if (pSys != nullptr)
	{
		delete pSys;
		_systems.remove(pSys);
		dispatchEvent(Event(EVENT_NETWORK_SYSTEM_TERMINATED));
	}
}
