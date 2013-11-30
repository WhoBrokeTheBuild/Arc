#pragma once

#ifndef __CONSOLE_PROGRAM_H__
#define __CONSOLE_PROGRAM_H__

#include "Common.h"
#include "Program.h"

namespace Arc
{
	class ConsoleProgram :
		public Program
	{
	public:

		inline ConsoleProgram( void ) { }

		virtual inline ~ConsoleProgram( void ) { }

		virtual inline void run( void ) { }

	}; // class ConsoleProgram

} // namespace Arc

#endif // __CONSOLE_PROGRAM_H__