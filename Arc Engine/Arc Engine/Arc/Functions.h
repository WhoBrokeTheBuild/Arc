
#pragma once

#ifndef __ARC_FUNCTIONS_H__
#define __ARC_FUNCTIONS_H__

#include "Defines.h"

#include <iostream>
#include <iomanip>
#include <sstream>

#include "TimeFunc.h"
#include "MathFunc.h"
#include "RandFunc.h"
#include "ParseFunc.h"
#include "StringFunc.h"
#include "InputFunc.h"

using std::string;
using std::stringstream;
using std::cin;
using std::cout;
using std::cerr;
using std::setw;
using std::left;
using std::ostream;

#ifndef endl
    #define endl "\n"
#endif

namespace Arc
{
    inline void dispMessage( string filename, int line, ostream& stream, string type, string source, string message )
    {
        stream << "[" << type << "] " << source << ": " << message << " (from " << basename(filename) << ":" << line << ")" << endl;
    }

    void dispError( string filename, int line, string source, string message );
    void dispInfo ( string filename, int line, string source, string message );

    inline void formatMessage( string filename, int line, ostream& stream, string type, string source, string format, ... )
    {
        va_list args;
        va_start(args, format);
        formatMessage(filename, line, stream, type, source, format, args);
        va_end(args);
    }

    inline void formatMessage( string filename, int line, ostream& stream, string type, string source, string format, va_list args )
    {
        static char buffer[100];
        vsprintf_s(buffer, format.c_str(), args);
        string message = string(buffer);

        dispMessage(filename, line, stream, type, source, message);
    }

    void formatError( string filename, int line, string source, string format, ... );
    void formatInfo ( string filename, int line, string source, string format, ... );

#ifdef ERROR
#undef ERROR
#endif

#ifdef DEBUG

#define ERROR(SRC, MSSG) dispError(string(__FILE__), __LINE__, SRC, MSSG)
#define INFO(SRC, MSSG)  dispInfo (string(__FILE__), __LINE__, SRC, MSSG)

#define ERRORF(SRC, FMT, ...) formatError(string(__FILE__), __LINE__, SRC, FMT, __VA_ARGS__)
#define INFOF(SRC, FMT, ...)  formatInfo (string(__FILE__), __LINE__, SRC, FMT, __VA_ARGS__)

#else

#define ERROR(SRC, MSSG)
#define INFO(SRC, MSSG)

#define ERRORF(SRC, FMT, ...)
#define INFOF(SRC, FMT, ...)

#endif

    inline void noop ( void ) { }
    void die  ( int errorLevel = EXIT_SUCCESS );
    void pause( const std::string msg = "Press enter to continue" );

    template <typename Value>
    bool arrayContains(unsigned int size, const Value list[], const Value& element)
    {
        for (unsigned int i = 0; i < size; ++i)
        {
            if (list[i] == element)
                return true;
        }

        return false;
    }

    template <typename Value>
    int arrayIndexOf(unsigned int size, const Value list[], const Value& element)
    {
        for (unsigned int i = 0; i < size; ++i)
        {
            if (list[i] == element)
                return i;
        }

        return -1;
    }

} // namespace Arc

#endif // __ARC_FUNCTIONS_H__
