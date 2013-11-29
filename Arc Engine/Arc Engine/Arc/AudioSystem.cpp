#include "AudioSystem.h"

const Arc::SystemComponentType Arc::AudioSystem::SYS_CMP_TYPE_AUDIO = "audio";

Arc::AudioSystem::AudioSystem( Program* pProgram )
	: SystemComponent(pProgram)
{
	INFO(toString(), "Initializing");

	addType(SYS_CMP_TYPE_AUDIO);

	_rate      = 44100;
	_chunkSize = 1024;
	_channels  = 2;
	_format    = MIX_DEFAULT_FORMAT;

	if (Mix_OpenAudio(_rate, _format, _channels, _chunkSize))
	{
		ERRORF(toString(), "Unable to open audio (%s)", Mix_GetError());
		die();
	}

	INFO(toString(), "Complete");
}

Arc::AudioSystem::~AudioSystem( void )
{
    INFO(toString(), "Terminating");

    Mix_CloseAudio();

    INFO(toString(), "Complete");
}
