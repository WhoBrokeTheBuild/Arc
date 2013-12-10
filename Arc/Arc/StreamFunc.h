#pragma once

#ifndef __ARC_STREAM_FUNC_H__
#define __ARC_STREAM_FUNC_H__

#include <iostream>
#include <string>

using std::ostream;
using std::istream;
using std::string;

namespace Arc
{
    int streamWriteBool  ( const bool   &value, ostream &stream );
    int streamWriteInt   ( const int    &value, ostream &stream );
    int streamWriteFloat ( const float  &value, ostream &stream );
    int streamWriteDouble( const double &value, ostream &stream );
    int streamWriteString( const string &value, ostream &stream );

    int streamReadBool  ( bool   &value, istream &stream );
    int streamReadInt   ( int    &value, istream &stream );
    int streamReadFloat ( float  &value, istream &stream );
    int streamReadDouble( double &value, istream &stream );
    int streamReadString( string &value, istream &stream );

} // namespace Arc

#endif // __ARC_STREAM_FUNC_H__
