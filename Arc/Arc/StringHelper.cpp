#include "StringHelper.h"
#include "ArrayList.h"

Arc::ArrayList<string> Arc::StringHelper::split( string str, char sep, int limit /*= -1*/ )
{
	ArrayList<string> stringParts;

	unsigned int lastEnd = 0;
	for (unsigned int i = 0; i < str.length(); ++i)
	{
		if (str[i] == sep)
		{
			if (limit != -1 && stringParts.getSize() >= (unsigned)limit - 1)
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

string Arc::StringHelper::join( string glue, ArrayList<string> pieces )
{
	return "";// TODO: Complete
}

string Arc::StringHelper::replaceOnce( string str, const string& sub, const string& newStr )
{
	unsigned int pos = str.find(sub);

	if (pos == string::npos)
		return str;

	return str.replace(pos, sub.length(), newStr);
}

string Arc::StringHelper::replaceAll( string str, const string& sub, const string& newStr )
{
	unsigned int pos = str.find(sub);

	while (pos != string::npos)
	{
		str.replace(pos, sub.length(), newStr);
		pos = str.find(sub, pos + newStr.length());
	}

	return str;
}

string Arc::StringHelper::substring( string str, unsigned int begin, int maxLength /*= -1 */ )
{
	if (begin >= str.length())
		return "";

	unsigned int fullMaxLength = (maxLength < 0 ? string::npos : unsigned(maxLength));

	return str.substr(begin, fullMaxLength);
}

bool Arc::StringHelper::isStringInString( string str, string sub )
{
	return (str.find(sub) != string::npos);
}
