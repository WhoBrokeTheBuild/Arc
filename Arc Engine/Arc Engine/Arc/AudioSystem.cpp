#include "AudioSystem.h"

Arc::AudioSystem::AudioSystem( void )
{
}

void Arc::AudioSystem::init( void )
{
    INFO(toString(), "Initializing");

    INFO(toString(), "Complete");
}

void Arc::AudioSystem::term( void )
{
    INFO(toString(), "Terminating");

    INFO(toString(), "Complete");
}
