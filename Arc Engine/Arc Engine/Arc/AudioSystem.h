#pragma once

#ifndef __ARC_AUDIO_SYSTEM_H__
#define __ARC_AUDIO_SYSTEM_H__

#include "Common.h"
#include "ManagedObject.h"

#include <AL/al.h>
#include <AL/alc.h>

namespace Arc
{
    class AudioSystem :
        public ManagedObject
    {
    protected:

		ALCdevice
			*_pDevice;

		ALCcontext
			*_pContext;

    public:

        AudioSystem( void );
        virtual ~AudioSystem( void );

        virtual inline string toString( void ) const { return "Audio System"; }

    }; // class AudioSystem

} // namespace Arc

#endif // __ARC_AUDIO_SYSTEM_H__
