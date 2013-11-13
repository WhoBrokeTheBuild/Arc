#pragma once

#ifndef __ARC_STRING_HELPER_H__
#define __ARC_STRING_HELPER_H__

#include <string>
#include "ArrayList.h"

using std::string;

namespace Arc
{
	class StringHelper
	{
	public:

		static ArrayList<string> split( string str, char sep, int limit = -1 );

		static inline string join( char glue, ArrayList<string> pieces ) { string strGlue; strGlue += glue; return StringHelper::join(strGlue, pieces); }

		static string join( string glue, ArrayList<string> pieces );

		static string replaceOnce( string str, const string& sub, const string& newStr );

		static string replaceAll( string str, const string& sub, const string& newStr );

		static string substring ( string str, unsigned int begin, int maxLength = -1 );

		static bool isStringInString( string str, string sub );

	}; // class StringHelper

} // namespace Arc

#endif // __ARC_STRING_HELPER_H__