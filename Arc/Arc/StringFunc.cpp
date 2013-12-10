#include "StringFunc.h"
#include "StringHelper.h"
#include "ArrayList.h"

string Arc::basename( string fullPath )
{
    char splitString = (fullPath.find("\\") != string::npos ? '\\' : '/');

    ArrayList<string> parts = StringHelper::split(fullPath, splitString);

    return parts[parts.getSize() - 1];
}

string Arc::shortToString( const short& value )
{
    return numToStr(value);
}

string Arc::intToString( const int& value )
{
    return numToStr(value);
}

string Arc::longToString( const long& value )
{
    return numToStr(value);
}

string Arc::floatToString( const float& value, int precision /*= 0*/ )
{
    return numToStr(value, precision);
}

string Arc::doubleToString( const double& value, int precision /*= 0*/ )
{
    return numToStr(value, precision);
}

string Arc::boolToString( const bool& value )
{
    return (value ? "true" : "false");
}
