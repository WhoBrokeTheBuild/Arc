#pragma once

#ifndef __ARC_PARSE_FUNC_H__
#define __ARC_PARSE_FUNC_H__

#include <string>
#include <sstream>

using std::string;
using std::stringstream;

namespace Arc
{
    class Vector2;
    class Circle;
    class Rect;
    class Color;

    int     parseInt    ( const string& value );
    float   parseFloat  ( const string& value );
    double  parseDouble ( const string& value );
    bool    parseBool   ( const string& value );
    Vector2 parseVector2( const string& value );
    Circle  parseCircle ( const string& value );
    Rect    parseRect   ( const string& value );
    Color   parseColor  ( const string& value );

} // namespace Arc

#endif // __ARC_PARSE_FUNC_H__
