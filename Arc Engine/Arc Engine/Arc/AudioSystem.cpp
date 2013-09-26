#include "AudioSystem.h"

Arc::AudioSystem::AudioSystem( void )
{
	INFO(toString(), "Initializing");

	_pDevice = alcOpenDevice(nullptr);

	if ( ! _pDevice)
	{
		ERRORF(toString(), "AL Failed to Open Device, %s", alGetError());
		die(1);
	}

	_pContext = alcCreateContext(_pDevice, nullptr);

	if ( ! alcMakeContextCurrent(_pContext))
	{
		ERRORF(toString(), "AL Failed to Make Context Current, %s", alGetError());
		die(1);
	}

	INFO(toString(), "Complete");
}

Arc::AudioSystem::~AudioSystem( void )
{
    INFO(toString(), "Terminating");

    INFO(toString(), "Complete");
}
