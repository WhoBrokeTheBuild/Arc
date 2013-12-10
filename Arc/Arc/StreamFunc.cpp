#include "StreamFunc.h"

int Arc::streamWriteBool( const bool &value, ostream &stream )
{
    stream.write((const char*) &value, sizeof(bool));
    return (int)sizeof(bool);
}

int Arc::streamWriteInt( const int &value, ostream &stream )
{
    stream.write((const char*) &value, sizeof(int));
    return (int)sizeof(int);
}

int Arc::streamWriteFloat( const float &value, ostream &stream )
{
    stream.write((const char*) &value, sizeof(float));
    return (int)sizeof(float);
}

int Arc::streamWriteDouble( const double &value, ostream &stream )
{
    stream.write((const char*) &value, sizeof(double));
    return (int)sizeof(double);
}

int Arc::streamWriteString( const string &value, ostream &stream )
{
    const static char terminator = '\0';

    stream.write(value.c_str(), value.length());
    stream.write((const char*)&terminator, 1); // end of string marker

    return value.length() + 1;
}

int Arc::streamReadBool( bool &value, istream &stream )
{
    stream.read((char*) &value, sizeof(bool));
    return (int)sizeof(bool);
}

int Arc::streamReadInt( int &value, istream &stream )
{
    stream.read((char*) &value, sizeof(int));
    return (int)sizeof(int);
}

int Arc::streamReadFloat( float &value, istream &stream )
{
    stream.read((char*) &value, sizeof(float));
    return (int)sizeof(float);
}

int Arc::streamReadDouble( double &value, istream &stream )
{
    stream.read((char*) &value, sizeof(double));
    return (int)sizeof(double);
}

int Arc::streamReadString( string &value, istream &stream )
{
    value = string(); // empty the string

    char c;
    while (!stream.eof())
    {
        stream.read((char*)&c, 1);

        if (c == '\0')
            break;

        value += c;
    }

    return value.length() + 1;
}
