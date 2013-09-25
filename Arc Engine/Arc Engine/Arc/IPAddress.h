#pragma once

#ifndef __ARC_IP_ADDRESS_H__
#define __ARC_IP_ADDRESS_H__

#include "Common.h"
#include "ManagedObject.h"

#include "ArrayList.h"

namespace Arc
{
	class Socket;

    class IPAddress :
        public ManagedObject
    {

		friend class Socket;

    protected:

        uint8_t
            _quads[4];

		inline uint8_t* getRawData( void ) { return _quads; }

    public:

		const static IPAddress
			ZERO;

		IPAddress( void );
		IPAddress( string addr );
        IPAddress( uint8_t a, uint8_t b, uint8_t c, uint8_t d );
        virtual inline  ~IPAddress( void ) { }

		virtual string toString( void ) const;

		bool operator==( const IPAddress& rhs ) const;
		bool operator!=( const IPAddress& rhs ) const;

    }; // class IPAddress

} // namespace Arc

#endif // __ARC_IP_ADDRESS_H__
