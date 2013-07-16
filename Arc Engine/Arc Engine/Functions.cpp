#include "Functions.h"

void die( int errorLevel /*= 0*/ )
{
    pause();
    exit(errorLevel);
}

void pause( string msg /*= "Press enter to continue" */ )
{
    static char ch;

    cout << msg;
    cin >> ch;
    cout << endl;
}
