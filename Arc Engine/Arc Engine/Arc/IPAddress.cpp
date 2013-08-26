#include "IPAddress.h"

Arc::IPAddress::IPAddress( void )
{
    _quads[0] = _quads[1] = _quads[2] = _quads[3] = 0;
}

Arc::IPAddress::IPAddress( string addr )
{
    ArrayList<string> strQuads = strSplit(addr, '.', 4);

    if (strQuads.size() < 4)
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

std::string Arc::IPAddress::toString( void )
{
    stringstream ss;
    ss << "IP Address ["
       << _quads[0] << ", " 
       << _quads[1] << ", "
       << _quads[2] << ", "
       << _quads[3] << "]";

    return ss.str();
}