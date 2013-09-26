#pragma once

#ifndef __ARC_AUDIO_SYSTEM_H__
#define __ARC_AUDIO_SYSTEM_H__

#include "Common.h"
#include "ManagedObject.h"

namespace Arc
{
    class AudioSystem :
        public ManagedObject
    {
    protected:


    public:

        AudioSystem( void );
        virtual ~AudioSystem( void ) { term(); }

        virtual void init( void );
        virtual void term( void );

        virtual inline string toString( void ) const { return "Audio System"; }

    }; // class AudioSystem

} // namespace Arc

#endif // __ARC_AUDIO_SYSTEM_H__
