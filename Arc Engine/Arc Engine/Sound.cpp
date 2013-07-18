#include "Sound.h"

/*
    Supported Formats: .wav, .aiff, .mid, .ogg, .mp3, .flac
*/
void Sound::init( string filename )
{
    _pChunk = Mix_LoadWAV(filename.c_str());
    _channel = -1;

    if (_pChunk == nullptr)
    {
        stringstream ss;
        ss << "Unable to load music (" << filename << ")";

        ERR(toString(), ss.str());
        return;
    }
}

void Sound::term( void )
{
    Mix_FreeChunk(_pChunk);
}

void Sound::update( const Event& event )
{

}

void Sound::play( bool loop /*= false */ )
{
    _channel = Mix_PlayChannel(-1, _pChunk, (loop ? -1 : 1));
}

void Sound::stop( void )
{
    if (_channel == -1)
        return;

    Mix_HaltChannel(_channel);
    _channel = -1;
}

float Sound::getVolume( void )
{
    return (float)Mix_VolumeChunk(_pChunk, -1) / (float)MIX_MAX_VOLUME;
}

void Sound::setVolume( float vol )
{
    vol = clamp(vol, 0.0f, 1.0f);
    Mix_VolumeChunk(_pChunk, (int)(vol * (float)MIX_MAX_VOLUME));
}

void Sound::fadeIn( double duration )
{

}

void Sound::fadeOut( double duration )
{

}

void Sound::stopFade( void )
{

}

bool Sound::isPlaying( void )
{
    return (_channel != -1);
}
