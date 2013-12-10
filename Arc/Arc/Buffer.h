#pragma once

#ifndef __ARC_BUFFER_H__
#define __ARC_BUFFER_H__

#include "Common.h"
#include "ManagedObject.h"

#include "ArrayList.h"
#include <iostream>
#include "MathHelper.h"

using std::istream;
using std::ostream;
using std::streamsize;

namespace Arc
{
	class ISerializable;

	// Modified from OpenFramework's ofBuffer
	class Buffer :
		public ManagedObject
	{
	protected:

		// Memory Buffer to store data in
		ArrayList<char> _buffer;

		// End of used memory buffer
		unsigned long _endOfUsed;

		// Index for reading from the buffer
		unsigned long _readIndex;

	public:

		inline Buffer( void )
			: _buffer(),
			  _endOfUsed(),
			  _readIndex()
		{
			clear();
		}

		inline Buffer( const Buffer& other )
			: _buffer(other._buffer),
			  _endOfUsed(other._endOfUsed),
			  _readIndex(other._readIndex)
		{ }

		Buffer( const char* buffer, unsigned int size );
		Buffer( const string& text );
		Buffer( istream& stream );

		virtual inline ~Buffer( void ) { clear(); }

		virtual inline string toString( void ) const { return "Buffer"; }

		inline void setDataFromBuffer( const Buffer& other ) { _buffer = other._buffer; }
		bool setDataFromStream( istream& stream );
		void setDataFromBuffer( const char* buffer, unsigned int size );
		void setDataFromString( const string& text );
		void setDataFromStringWithLength( const string& text );

		void appendBuffer( const Buffer& other );
		bool appendDataFromStream( istream& stream );
		void appendBuffer( const char* buffer, unsigned int size );
		void appendString( const string& text );
		void appendStringWithLength( const string& text );
		void appendBool( const bool& value );
		void appendShort( const short& value );
		void appendInt( const int& value );
		void appendLong( const long& value );
		void appendChar( const char& value );
		void appendFloat( const float& value );
		void appendDouble( const double& value );

		void appendSerialized( ISerializable& ser );

		string readNextString( unsigned int size );
		string readNextStringWithLength( void );
		bool readNextBool( void );
		short readNextShort( void );
		int readNextInt( void );
		long readNextLong( void );
		char readNextChar( void );
		float readNextFloat( void );
		double readNextDouble( void );

		inline bool endOfBuffer( void ) { return (_readIndex >= _endOfUsed); }

		string readStringAt( unsigned long offset, unsigned int size );
		string readStringWithLengthAt( unsigned long offset );
		bool readBoolAt( unsigned long offset );
		short readShortAt( unsigned long offset );
		int readIntAt( unsigned long offset );
		long readLongAt( unsigned long offset );
		char readCharAt( unsigned long offset );
		float readFloatAt( unsigned long offset );
		double readDoubleAt( unsigned long offset );

		bool writeToStream( ostream& stream ) const;

		void setEndOfUsed( unsigned int index ) { _endOfUsed = MathHelper::clamp(index, unsigned(0), _buffer.getSize() - 1);}

		void clear( void );

		string getText( void ) const;
		Buffer& operator=( const string& text );

		void resize( long size );
		inline long getFullSize( void ) const { return _buffer.getSize() - 1; }
		inline long getUsedSize( void ) const { return _endOfUsed; }

		inline char* getRawBuffer( void ) { return (char*)&(_buffer[0]); }
		inline char* getRawBuffer( void ) const { return (char*)&(_buffer[0]); }

		friend inline ostream& operator<<( ostream& stream, const Buffer& buffer)
		{
			buffer.writeToStream(stream);
			return stream;
		}

		friend inline istream& operator>>( istream& stream, Buffer& buffer)
		{
			buffer.appendDataFromStream(stream);
			return stream;
		}


	}; // class Buffer

} // namespace Arc

#endif // __ARC_BUFFER_H__