#include "Sound.h"

/*
    Supported Formats: .wav, .aiff, .mid, .ogg, .mp3, .flac
*/
Arc::Sound::Sound( string filename )
	: _pChunk(nullptr),
	  _channel(-1)
{
	_pChunk = Mix_LoadWAV(filename.c_str());

	if (_pChunk == nullptr)
	{
		ERRORF(toString(), "Unable to load sound (file: %s) error: %s", filename.c_str(), Mix_GetError());
		return;
	}
}

Arc::Sound::~Sound( void )
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
