#include "Buffer.h"

Arc::Buffer::Buffer( const char* buffer, unsigned int size )
{
	setData(buffer, size);
}

Arc::Buffer::Buffer( const string& text )
{
	setData(text);
}

Arc::Buffer::Buffer( istream& stream )
{
	setData(stream);
}

void Arc::Buffer::setData( const char* buffer, unsigned int size )
{
	clear();
	_buffer.assign(buffer, buffer + size);
	_buffer.resize(_buffer.getSize() + 1, 0);
}

void Arc::Buffer::setData( const string& text )
{
	setData(text.c_str(), text.size());
}

bool Arc::Buffer::setData( istream& stream )
{
	clear();
	return appendData(stream);
}

bool Arc::Buffer::writeToStream( ostream& stream ) const
{
	if (stream.bad())
		return false;

	stream.write(&_buffer[0], _buffer.getSize() - 1);
	return true;
}

void Arc::Buffer::clear( void )
{
	_buffer.resize(1);
	_buffer[0] = 0;
}

string Arc::Buffer::getText( void ) const
{
	if (_buffer.isEmpty())
		return "";

	return &_buffer[0];
}

long Arc::Buffer::getSize( void ) const
{
	return _buffer.getSize() - 1;
}

Arc::Buffer::operator string( void ) const
{
	return getText();
}

void Arc::Buffer::resize( long size )
{
	_buffer.resize(size + 1);
	_buffer.back() = 0;
}

void Arc::Buffer::appendData( const Buffer& other )
{
	appendData(&(other._buffer[0]), other.getSize());
}

void Arc::Buffer::appendData( const char* buffer, unsigned int size )
{
	_buffer.insert(_buffer.end() - 1, buffer, buffer + size);
	_buffer.back() = 0;
}

void Arc::Buffer::appendData( const string& text )
{
	appendData(text.c_str(), text.size());
}

bool Arc::Buffer::appendData( istream& stream )
{
	if (stream.bad())
		return false;

	const int TMP_BUFFER_SIZE = 1024;

	char tmp_buffer[TMP_BUFFER_SIZE];
	streamsize size = getSize();
	streamsize n = 0;
	do 
	{
		stream.read(tmp_buffer, TMP_BUFFER_SIZE);
		n = stream.gcount();
		_buffer.resize((unsigned int)(size + n + 1), 0);
		memcpy(&(_buffer[0]) + size, tmp_buffer, (unsigned int)n);
		size += n;

		if ( ! stream )
			break;
	} 
	while (n > 0);

	return true;
}
