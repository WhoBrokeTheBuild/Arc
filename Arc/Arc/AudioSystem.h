#pragma once

#ifndef __ARC_AUDIO_SYSTEM_H__
#define __ARC_AUDIO_SYSTEM_H__

#include "Common.h"
#include "SystemComponent.h"

#include <SDL/SDL_mixer.h>

namespace Arc
{
    class AudioSystem :
        public SystemComponent
    {
    protected:

        int _rate;
		int _channels;
		int _chunkSize; 

        uint16_t _format;

    public:

		static const SystemComponentType SYS_CMP_TYPE_AUDIO;

        AudioSystem( Program* pProgram );
        virtual ~AudioSystem( void );

        virtual inline string toString( void ) const { return "Audio System"; }

    }; // class AudioSystem

} // namespace Arc

#endif // __ARC_AUDIO_SYSTEM_H__
