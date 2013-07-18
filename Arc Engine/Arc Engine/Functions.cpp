#include "Functions.h"

void die( int errorLevel /*= 0*/ )
{
    pause();
    exit(errorLevel);
}

void pause( const string msg /*= "Press enter to continue"*/ )
{
    static string tmp;
    cout << msg;
    getline(cin, tmp);
    cout << endl;
}
