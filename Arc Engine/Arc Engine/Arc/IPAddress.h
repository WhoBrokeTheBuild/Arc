#pragma once

#ifndef __ARC_IP_ADDRESS_H__
#define __ARC_IP_ADDRESS_H__

#include "Common.h"
#include "ManagedObject.h"

#include "ArrayList.h"

namespace Arc
{
	class Socket;

	/* A class representing an IPv4 32-bit address
	 */
    class IPAddress :
        public ManagedObject
    {

		friend class Socket;

    protected:

		// Four unsigned bytes representing the IPv4 address
        uint8_t _quads[4];

		// Returns the quads as an array
		inline uint8_t* getRawData( void ) { return _quads; }

    public:

		// Constant value of 0.0.0.0
		const static IPAddress ZERO;

		/* Creates an address of zeros
		 */
		IPAddress( void );

		/* Creates an address from a string in decimal dotted notation, eg. "1.2.3.4"
		 *
		 * @param address: The string of the address to parse
		 */
		IPAddress( string address );

		/* Creates an address from four separate bytes
		 *
		 * @param a: The first quad
		 * @param b: The second quad
		 * @param c: The third quad
		 * @param d: The fourth quad
		 */
        IPAddress( uint8_t a, uint8_t b, uint8_t c, uint8_t d );

        virtual inline ~IPAddress( void ) { }

		virtual string toString( void ) const;
		
		/* Preforms a DNS lookup on the given hostname
		 *
		 * @param hostname: The hostname to check
		 * @returns: The first IP address of the host, or 0.0.0.0 on failure
		 */
		static IPAddress lookup( string hostname );

		bool operator==( const IPAddress& rhs ) const;
		bool operator!=( const IPAddress& rhs ) const;

    }; // class IPAddress

} // namespace Arc

#endif // __ARC_IP_ADDRESS_H__
