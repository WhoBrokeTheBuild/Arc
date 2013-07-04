#include "Functions.h"

void die( int errorLevel /*= 0*/ )
{
    pause();
    exit(errorLevel);
}

void pause( void )
{
    cout << "Press any key to continue";
    _getch();
    cout << endl;
}
