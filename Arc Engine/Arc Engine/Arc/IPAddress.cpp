#include "IPAddress.h"
#include "Socket.h"
#include "StringHelper.h"

const Arc::IPAddress Arc::IPAddress::ZERO = IPAddress(0, 0, 0, 0);

Arc::IPAddress::IPAddress( void )
{
    _quads[0] = _quads[1] = _quads[2] = _quads[3] = 0;
}

Arc::IPAddress::IPAddress( string addr )
{
    ArrayList<string> strQuads = StringHelper::split(addr, '.', 4);

    if (strQuads.getSize() < 4)
        _quads[0] = _quads[1] = _quads[2] = _quads[3] = 0;

    for (unsigned int i = 0; i < 4; ++i)
        _quads[i] = (uint8_t)parseInt(strQuads[i]);
}

Arc::IPAddress::IPAddress( uint8_t a, uint8_t b, uint8_t c, uint8_t d )
{
    _quads[0] = a;
    _quads[1] = b;
    _quads[2] = c;
    _quads[3] = d;
}

std::string Arc::IPAddress::toString( void ) const
{
    stringstream ss;
    ss << "IP Address ["
		<< (int)_quads[0] << "."
		<< (int)_quads[1] << "."
		<< (int)_quads[2] << "."
		<< (int)_quads[3] << "]";

    return ss.str();
}

bool Arc::IPAddress::operator==( const IPAddress& rhs ) const
{
	return ( _quads[0] == rhs._quads[0] &&
		     _quads[1] == rhs._quads[1] &&
			 _quads[2] == rhs._quads[2] &&
			 _quads[3] == rhs._quads[3] );
}

bool Arc::IPAddress::operator!=( const IPAddress& rhs ) const
{
	return !(*this == rhs);
}
