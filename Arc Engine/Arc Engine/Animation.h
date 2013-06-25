#pragma once

#ifndef __ANIMATION_H__
#define __ANIMATION_H__

#include "ArcCommon.h"
#include "EventDispatcher.h"

#include <vector>

#include "Sprite.h"

class Animation :
    public EventDispatcher
{
private:

    vector<Sprite*>
        _frames;

public:

    bool
        Animating,
        Looping;

    Animation( void );
    virtual ~Animation( void );

    virtual string toString( void ) const;

    virtual void init( vector<Sprite*> frames = vector<Sprite*>(), bool animating = false, bool looping = false );
    virtual void term( void );

    virtual bool hasFrame( int frame );
    virtual void addFrame( Sprite* pFrame );
    virtual bool removeFrame( Sprite* pFrame );
    virtual bool removeFrame( int pFrame );

    virtual Size frameSize( int frame );
    virtual Sprite* frameAt( int frame );
    virtual int length( void ) { return (int)_frames.size(); }

};

#endif