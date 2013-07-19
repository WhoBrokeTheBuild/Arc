#include "StringFunc.h"
#include "ArrayList.h"

Arc::ArrayList<string> Arc::strSplit( string str, char sep, int limit /*= -1*/ )
{
    ArrayList<string> stringParts;

    unsigned int lastEnd = 0;
    for (unsigned int i = 0; i < str.length(); ++i)
    {
        if (str[i] == sep)
        {
            if (limit != -1 && stringParts.size() >= (unsigned)limit - 1)
            {
                break;
            }
            stringParts.add(str.substr(lastEnd, i - lastEnd));
            lastEnd = i + 1;
        }
    }

    if (lastEnd < str.length())
    {
        stringParts.add(str.substr(lastEnd));
    }

    return stringParts;
}

string Arc::strReplace( string str, const string& sub, const string& newStr )
{
    unsigned int pos = str.find(sub);

    if (pos == string::npos)
        return str;

    return str.replace(pos, sub.length(), newStr);
}

string Arc::strReplaceAll( string str, const string& sub, const string& newStr )
{
    unsigned int pos = str.find(sub);

    while (pos != string::npos)
    {
        str.replace(pos, sub.length(), newStr);
        pos = str.find(sub, pos + newStr.length());
    }

    return str;
}

string Arc::strSubstring( string str, unsigned int begin, int maxLength /*= -1 */ )
{
    if (begin >= str.length())
        return "";

    if (maxLength == -1)
        maxLength = string::npos;

    return str.substr(begin, maxLength);
}

bool Arc::strContains( string str, string sub )
{
    return (str.find(sub) != string::npos);
}

string Arc::basename( string fullPath )
{
    char splitString = (fullPath.find("\\") != string::npos ? '\\' : '/');

    ArrayList<string> parts = strSplit(fullPath, splitString);

    return parts[parts.size() - 1];
}

string Arc::shortToStr( const short& value )
{
    return numToStr(value);
}

string Arc::intToStr( const int& value )
{
    return numToStr(value);
}

string Arc::longToStr( const long& value )
{
    return numToStr(value);
}

string Arc::floatToStr( const float& value )
{
    return numToStr(value);
}

string Arc::doubleToStr( const double& value )
{
    return numToStr(value);
}

string Arc::boolToStr( const bool& value )
{
    return (value ? "true" : "false");
}
