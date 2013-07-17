#include "StringFunc.h"
#include "ArrayList.h"

ArrayList<string> strSplit( string str, char sep, int limit /*= -1*/ )
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

std::string strReplace( string str, const string& sub, const string& newStr )
{
    int pos = str.find(sub);

    if (pos == std::string::npos)
        return str;

    return str.replace(pos, sub.length(), newStr);
}

std::string strReplaceAll( string str, const string& sub, const string& newStr )
{
    int pos = str.find(sub);

    while (pos != string::npos)
    {
        str.replace(pos, sub.length(), newStr);
        pos = str.find(sub, pos + newStr.length());
    }

    return str;
}

std::string strSubstring( string str, unsigned int begin, int maxLength /*= -1 */ )
{
    if (begin >= str.length())
        return "";

    if (maxLength == -1)
        maxLength = string::npos;

    return str.substr(begin, maxLength);
}

bool strContains( string str, string sub )
{
    return (str.find(sub) != string::npos);
}

string basename( string fullPath )
{
    char splitString = (fullPath.find("\\") != string::npos ? '\\' : '/');

    ArrayList<string> parts = strSplit(fullPath, splitString);

    return parts[parts.size() - 1];
}
