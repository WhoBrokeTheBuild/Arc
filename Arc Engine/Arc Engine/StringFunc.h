#pragma once

#ifndef __STRING_FUNC_H__
#define __STRING_FUNC_H__

#include <string>
#include <sstream>

using namespace std;

template <class T>
class ArrayList;

ArrayList<string> strSplit     ( string str, char sep, int limit = -1 );
string            strReplace   ( string str, const string& sub, const string& newStr );
string            strReplaceAll( string str, const string& sub, const string& newStr );
string            strSubstring ( string str, unsigned int begin, int maxLength = -1 );
bool              strContains  ( string str, string sub );

string basename( string fullPath );

string boolToString  ( const bool& value );
string intToString   ( const int& value );
string floatToString ( const float& value );
string doubleToString( const double& value );

#endif
