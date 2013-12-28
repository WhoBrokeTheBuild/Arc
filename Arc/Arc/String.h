#pragma once

#ifndef __ARC_STRING_H__
#define __ARC_STRING_H__

#include "Common.h"
#include "ManagedObject.h"

namespace Arc
{
	class String :
		public ManagedObject
	{
	protected:

		string
			_string;

	public:

		inline String( void )
			: _string()
		{ }

		inline String( const string& other )
			: _string(other)
		{ }

		inline String( const String& other )
			: _string(other._string)
		{ }

		inline String( const char* cstr )
			: _string(cstr)
		{ }

		virtual inline ~String( void ) { }

	};

}

#endif // __ARC_STRING_H__