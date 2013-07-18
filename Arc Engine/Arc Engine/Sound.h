#pragma once

#ifndef __SOUND_H__
#define __SOUND_H__

#include "ArcCommon.h"
#include "GameObject.h"
#include "IFrameListener.h"

#include <SDL/SDL_mixer.h>

class Sound :
    public GameObject,
    public IFrameListener
{
protected:

    Mix_Chunk
        *_pChunk;

    int
        _channel;

public:

    Sound( void ) { }
    virtual ~Sound( void ) { term(); }

    virtual void init( string filename );
    virtual void term( void );

    virtual string toString( void ) const { return "Sound"; }

    virtual void update( const Event& event );

    virtual void play( bool loop = false );
    virtual void stop( void );

    virtual bool isPlaying( void );

    virtual float getVolume( void );
    virtual void  setVolume( float vol );

    virtual void fadeIn  ( double duration );
    virtual void fadeOut ( double duration );
    virtual void stopFade( void );

};

#endif