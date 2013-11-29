#pragma once

#ifndef __ARC_SCRIPTING_SYSTEM_H__
#define __ARC_SCRIPTING_SYSTEM_H__

#include "Common.h"
#include "SystemComponent.h"

#include "Timer.h"

extern "C"
{
    #include <lua.h>
    #include <lualib.h>
    #include <lauxlib.h>
}

namespace Arc
{
    class Program;
    class GraphicsSystem;

	/** A system for managing and interfacing with Lua
	  */
    class ScriptingSystem :
        public SystemComponent
    {
    protected:

		// The lua_State used to interact with a lua instance
        lua_State
            *_pLuaState;

    public:

		static const SystemComponentType SYS_CMP_TYPE_SCRIPTING;

        ScriptingSystem( Program* pProgram );
        virtual ~ScriptingSystem( void );

        virtual inline string toString( void ) const { return "Scripting System"; }

		// Connect lua_* functions in C++ to arc_* functions in lua
        virtual void registerFunctions( void );

		// Load an execute a lua file
        virtual void executeFile( string filename );
		
		// Display lua errors
        virtual void showErrors( int status );

    }; // class ScriptingSystem

	// Wrapper functions for utility functions
    int lua_die  ( lua_State* state );
    int lua_info ( lua_State* state );
    int lua_error( lua_State* state );
    int lua_sleep( lua_State *state );

	// Wrapper functions for window management functions
    int lua_set_window_title( lua_State* state );
    int lua_set_window_size ( lua_State* state );

} // namespace Arc

#endif // __ARC_SCRIPTING_SYSTEM_H__
