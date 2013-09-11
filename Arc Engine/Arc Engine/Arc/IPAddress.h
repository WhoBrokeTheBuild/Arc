#pragma once

#ifndef __ARC_IP_ADDRESS_H__
#define __ARC_IP_ADDRESS_H__

#include "Common.h"
#include "ManagedObject.h"

#include "ArrayList.h"

namespace Arc
{
    class IPAddress :
        public ManagedObject
    {
    protected:

        uint8_t
            _quads[4];

    public:

        IPAddress( void );
        IPAddress( string addr );
        IPAddress( uint8_t a, uint8_t b, uint8_t c, uint8_t d );
        virtual inline  ~IPAddress( void ) { }

        virtual string toString( void ) const;

    }; // class IPAddress

} // namespace Arc

#endif // __ARC_IP_ADDRESS_H__
