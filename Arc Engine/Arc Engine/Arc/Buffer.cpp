#include "Buffer.h"
#include "ISerializable.h"

Arc::Buffer::Buffer( const char* buffer, unsigned int size )
{
	setDataFromBuffer(buffer, size);
}

Arc::Buffer::Buffer( const string& text )
{
	setDataFromString(text);
}

Arc::Buffer::Buffer( istream& stream )
{
	setDataFromStream(stream);
}

bool Arc::Buffer::setDataFromStream( istream& stream )
{
	clear();
	return appendDataFromStream(stream);
}

void Arc::Buffer::setDataFromBuffer( const char* buffer, unsigned int size )
{
	clear();
	_buffer.resize(_buffer.getSize() + size + 1, 0);
	_buffer.assign(buffer, buffer + size);
}

void Arc::Buffer::setDataFromString( const string& text )
{
	setDataFromBuffer(text.c_str(), text.size());
}

void Arc::Buffer::setDataFromStringWithLength( const string& text )
{
	clear();
	appendShort(text.size());
	appendString(text);
}

void Arc::Buffer::appendBuffer( const Buffer& other )
{
	appendBuffer(&(other._buffer[0]), other.getFullSize());
}

void Arc::Buffer::appendBuffer( const char* buffer, unsigned int size )
{
	_buffer.insert(_buffer.begin() + _endOfUsed, buffer, buffer + size);
	_endOfUsed += size;
	_buffer[_endOfUsed + 1] = 0;
}

bool Arc::Buffer::appendDataFromStream( istream& stream )
{
	if (stream.bad())
		return false;

	const int TMP_BUFFER_SIZE = 1024;

	char tmp_buffer[TMP_BUFFER_SIZE];
	streamsize size = getFullSize();
	streamsize n = 0;
	do 
	{
		stream.read(tmp_buffer, TMP_BUFFER_SIZE);
		n = stream.gcount();

		if (_endOfUsed + n > size)
		{
			streamsize overflow = (_endOfUsed + n) - size;
			_buffer.resize((unsigned int)(size + overflow + 1), 0);
		}

		memcpy(&(_buffer[0]) + _endOfUsed, tmp_buffer, (unsigned int)n);
		_endOfUsed += unsigned(n);

		if ( ! stream )
			break;
	} 
	while (n > 0);

	return true;
}

void Arc::Buffer::appendString( const string& text )
{
	appendBuffer(text.c_str(), text.size());
}

void Arc::Buffer::appendStringWithLength( const string& text )
{
	appendShort(text.size());
	appendBuffer(text.c_str(), text.size());
}

void Arc::Buffer::appendBool( const bool& value )
{
	appendBuffer((char*)&value, sizeof(bool));
}

void Arc::Buffer::appendShort( const short& value )
{
	appendBuffer((char*)&value, sizeof(short));
}

void Arc::Buffer::appendInt( const int& value )
{
	appendBuffer((char*)&value, sizeof(int));
}

void Arc::Buffer::appendLong( const long& value )
{
	appendBuffer((char*)&value, sizeof(long));
}

void Arc::Buffer::appendChar( const char& value )
{
	appendBuffer((char*)&value, sizeof(char));
}

void Arc::Buffer::appendFloat( const float& value )
{
	appendBuffer((char*)&value, sizeof(float));
}

void Arc::Buffer::appendDouble( const double& value )
{
	appendBuffer((char*)&value, sizeof(double));
}

void Arc::Buffer::appendSerialized( ISerializable& ser )
{
	ser.serialize(*this);
}

bool Arc::Buffer::writeToStream( ostream& stream ) const
{
	if (stream.bad())
		return false;

	// Ignore trailing 0 for strings
	stream.write(&_buffer[0], _buffer.getSize() - 1);
	return true;
}

void Arc::Buffer::clear( void )
{
	_endOfUsed = 0;
	_buffer.resize(1);
	_buffer[0] = 0;
}

string Arc::Buffer::getText( void ) const
{
	if (_buffer.isEmpty())
		return "";

	return &_buffer[0];
}

void Arc::Buffer::resize( long size )
{
	if (_endOfUsed > unsigned(size))
		_endOfUsed = size;

	if (_readIndex > unsigned(size))
		_readIndex = size;

	_buffer.resize(size + 1);
	_buffer.back() = 0;
}

Arc::Buffer& Arc::Buffer::operator=( const string& text )
{
	setDataFromString(text);
	return *this;
}

string Arc::Buffer::readNextString( unsigned int size )
{
	string val = readStringAt(_readIndex, size);
	_readIndex += size;
	return val;
}

string Arc::Buffer::readNextStringWithLength( void )
{
	string val = readStringWithLengthAt(_readIndex);
	_readIndex += sizeof(short); // For the string length stored in the buffer
	_readIndex += val.length();
	return val;
}

bool Arc::Buffer::readNextBool( void )
{
	bool val = readBoolAt(_readIndex);
	_readIndex += sizeof(bool);
	return val;
}

short Arc::Buffer::readNextShort( void )
{
	short val = readShortAt(_readIndex);
	_readIndex += sizeof(short);
	return val;
}

int Arc::Buffer::readNextInt( void )
{
	int val = readIntAt(_readIndex);
	_readIndex += sizeof(int);
	return val;
}

long Arc::Buffer::readNextLong( void )
{
	long val = readLongAt(_readIndex);
	_readIndex += sizeof(long);
	return val;
}

char Arc::Buffer::readNextChar( void )
{
	char val = readCharAt(_readIndex);
	_readIndex += sizeof(char);
	return val;
}

float Arc::Buffer::readNextFloat( void )
{
	float val = readFloatAt(_readIndex);
	_readIndex += sizeof(float);
	return val;
}

double Arc::Buffer::readNextDouble( void )
{
	double val = readDoubleAt(_readIndex);
	_readIndex += sizeof(double);
	return val;
}

string Arc::Buffer::readStringAt( unsigned long offset, unsigned int size )
{
	char* buffer = new char[size + 1];

	memcpy(buffer, &(_buffer[0]) + offset, size);

	buffer[size] = '\0';
	string data = string(buffer);

	delete[] buffer;

	return data;
}

string Arc::Buffer::readStringWithLengthAt( unsigned long offset )
{
	short size = readShortAt(offset);
	return readStringAt(offset + sizeof(short), size);
}

bool Arc::Buffer::readBoolAt( unsigned long offset )
{
	bool val;
	memcpy(&val, &(_buffer[0]) + offset, sizeof(bool));
	return val;
}

short Arc::Buffer::readShortAt( unsigned long offset )
{
	short val;
	memcpy(&val, &(_buffer[0]) + offset, sizeof(short));
	return val;
}

int Arc::Buffer::readIntAt( unsigned long offset )
{
	int val;
	memcpy(&val, &(_buffer[0]) + offset, sizeof(int));
	return val;
}

long Arc::Buffer::readLongAt( unsigned long offset )
{
	long val;
	memcpy(&val, &(_buffer[0]) + offset, sizeof(long));
	return val;
}

char Arc::Buffer::readCharAt( unsigned long offset )
{
	char val;
	memcpy(&val, &(_buffer[0]) + offset, sizeof(char));
	return val;
}

float Arc::Buffer::readFloatAt( unsigned long offset )
{
	float val;
	memcpy(&val, &(_buffer[0]) + offset, sizeof(float));
	return val;
}

double Arc::Buffer::readDoubleAt( unsigned long offset )
{
	double val;
	memcpy(&val, &(_buffer[0]) + offset, sizeof(double));
	return val;
}
