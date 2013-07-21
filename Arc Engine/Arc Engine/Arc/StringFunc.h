#pragma once

#ifndef __ARC_STRING_FUNC_H__
#define __ARC_STRING_FUNC_H__

#include <string>
#include <sstream>

using std::string;
using std::stringstream;

namespace Arc
{
    template <class T>
    class ArrayList;

    ArrayList<string> strSplit     ( string str, char sep, int limit = -1 );
    string            strReplace   ( string str, const string& sub, const string& newStr );
    string            strReplaceAll( string str, const string& sub, const string& newStr );
    string            strSubstring ( string str, unsigned int begin, int maxLength = -1 );
    bool              strContains  ( string str, string sub );

    string basename( string fullPath );

    template <class Number>
    string numToStr( const Number& value )
    {
        stringstream ss;
        ss << value;
        return ss.str();
    }

    string shortToStr ( const short&  value );
    string intToStr   ( const int&    value );
    string longToStr  ( const long&   value );
    string floatToStr ( const float&  value );
    string doubleToStr( const double& value );
    string boolToStr  ( const bool&   value );

} // namespace Arc

#endif // __ARC_STRING_FUNC_H__
