#pragma once

#ifndef __ARC_BUFFER_H__
#define __ARC_BUFFER_H__

#include "Common.h"
#include "ManagedObject.h"

#include "ArrayList.h"
#include <iostream>

using std::istream;
using std::ostream;
using std::streamsize;

namespace Arc
{
	// Modified from OpenFramework's ofBuffer
	class Buffer :
		public ManagedObject
	{
	protected:

		// Memory Buffer to store data in
		ArrayList<char> _buffer;

	public:

		inline Buffer( void )
			: _buffer()
		{ }

		inline Buffer( const Buffer& other )
			: _buffer(other._buffer)
		{ }

		Buffer( const char* buffer, unsigned int size );

		Buffer( const string& text );

		Buffer( istream& stream );

		virtual inline ~Buffer( void ) { clear(); }

		virtual inline string toString( void ) const { return "Buffer"; }

		inline void setData( const Buffer& other ) { _buffer = other._buffer; }
		void setData( const char* buffer, unsigned int size );
		void setData( const string& text );
		bool setData( istream& stream );

		void appendData( const Buffer& other );
		void appendData( const char* buffer, unsigned int size );
		void appendData( const string& text );
		bool appendData( istream& stream );

		bool writeToStream( ostream& stream ) const;

		void clear( void );

		string getText( void ) const;
		operator string( void ) const;
		Buffer& operator=( const string& text );

		void resize( long size );
		long getSize( void ) const;

		friend ostream& operator<<( ostream& stream, const Buffer& buffer);
		friend istream& operator>>( istream& stream, Buffer& buffer);


	}; // class Buffer

} // namespace Arc

#endif // __ARC_BUFFER_H__