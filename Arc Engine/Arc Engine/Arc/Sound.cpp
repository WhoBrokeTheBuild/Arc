#include "Sound.h"

Arc::Sound::Sound( void )
{
    _pChunk  = nullptr;
    _channel = 0;
}

/*
    Supported Formats: .wav, .aiff, .mid, .ogg, .mp3, .flac
*/
void Arc::Sound::init( string filename )
{
    _pChunk = Mix_LoadWAV(filename.c_str());
    _channel = -1;

    if (_pChunk == nullptr)
    {
        stringstream ss;
        ss << "Unable to load music (" << filename << ")";

        ERROR(toString(), ss.str());
        return;
    }
}

void Arc::Sound::term( void )
{
    Mix_FreeChunk(_pChunk);
}

void Arc::Sound::update( const Event& event )
{

}

void Arc::Sound::play( bool loop /*= false */ )
{
    _channel = Mix_PlayChannel(-1, _pChunk, (loop ? -1 : 0));
}

void Arc::Sound::stop( void )
{
    if (_channel == -1)
        return;

    Mix_HaltChannel(_channel);
    _channel = -1;
}

bool Arc::Sound::isPlaying( void )
{
    return (_channel != -1);
}

float Arc::Sound::getVolume( void )
{
    return (float)Mix_VolumeChunk(_pChunk, -1) / (float)MIX_MAX_VOLUME;
}

void Arc::Sound::setVolume( float vol )
{
    vol = clamp(vol, 0.0f, 1.0f);
    Mix_VolumeChunk(_pChunk, (int)(vol * (float)MIX_MAX_VOLUME));
}

void Arc::Sound::fadeIn( double duration )
{

}

void Arc::Sound::fadeOut( double duration )
{

}

void Arc::Sound::stopFade( void )
{

}
