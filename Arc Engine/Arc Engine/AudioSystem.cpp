#include "AudioSystem.h"

void AudioSystem::init( void )
{
    INF(toString(), "Initializing");

    _rate      = 44100;
    _chunkSize = 1024;
    _channels  = 2;
    _format    = MIX_DEFAULT_FORMAT;

    if (Mix_OpenAudio(_rate, _format, _channels, _chunkSize))
    {
        stringstream ss;
        ss << "Unable to open audio (" << Mix_GetError() << ")";

        ERR(toString(), ss.str());
        die();
    }

    INF(toString(), "Complete");
}

void AudioSystem::term( void )
{
    Mix_CloseAudio();
}
 