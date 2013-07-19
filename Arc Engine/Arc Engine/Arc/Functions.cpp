#include "Functions.h"

void Arc::die( int errorLevel /*= 0*/ )
{
    pause();
    exit(errorLevel);
}

void Arc::pause( const std::string msg /*= "Press enter to continue"*/ )
{
    static string tmp;
    cout << msg;
    cin.clear();
    getline(cin, tmp);
    cout << endl;
}
