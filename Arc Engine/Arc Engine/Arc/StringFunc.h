#pragma once

#ifndef __ARC_STRING_FUNC_H__
#define __ARC_STRING_FUNC_H__

#include <string>
#include <sstream>

using std::string;
using std::stringstream;

namespace Arc
{

    string basename( string fullPath );

    template <class Number>
    inline string numToStr( const Number& value )
    {
        stringstream ss;
        ss << value;
        return ss.str();
    }

    string shortToString ( const short&  value );
    string intToString   ( const int&    value );
    string longToString  ( const long&   value );
    string floatToString ( const float&  value );
    string doubleToString( const double& value );
    string boolToString  ( const bool&   value );

} // namespace Arc

#endif // __ARC_STRING_FUNC_H__
