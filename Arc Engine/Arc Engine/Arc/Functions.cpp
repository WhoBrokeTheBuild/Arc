#include "Functions.h"

void Arc::die( int errorLevel /*= EXIT_SUCCESS*/ )
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

void Arc::dispError( string filename, int line, string source, string message )
{
    dispMessage(filename, line, cerr, "Error", source, message);
}

void Arc::dispInfo( string filename, int line, string source, string message )
{
    dispMessage(filename, line, cout, "Info", source, message);
}

void Arc::formatError( string filename, int line, string source, string format, ... )
{
    va_list args;
    va_start(args, format);
    formatMessage(filename, line, cerr, "Error", source, format, args);
    va_end(args);
}

void Arc::formatInfo( string filename, int line, string source, string format, ... )
{
    va_list args;
    va_start(args, format);
    formatMessage(filename, line, cerr, "Info", source, format, args);
    va_end(args);
}
