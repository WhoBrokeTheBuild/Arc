#pragma once

#ifndef __ARC_SCRIPTING_SYSTEM_H__
#define __ARC_SCRIPTING_SYSTEM_H__

#include "Common.h"
#include "ManagedObject.h"

#include "Timer.h"

extern "C"
{
    #include <lua.h>
    #include <lualib.h>
    #include <lauxlib.h>
};

namespace Arc
{
    class Program;
    class GraphicsSystem;

    class ScriptingSystem :
        public ManagedObject
    {
    protected:
        
        lua_State
            *_pLuaState;

    public:

        ScriptingSystem( void )
            : _pLuaState(nullptr)
        { }

        virtual ~ScriptingSystem( void ) { term(); }

        virtual void init( void );
        virtual void term( void );

        virtual inline string toString( void ) const { return "Scripting System"; }

        virtual void registerFunctions( void );

        virtual void executeFile( string filename );

        virtual void showErrors( int status );

    }; // class ScriptingSystem

    int lua_die  ( lua_State* state );
    int lua_info ( lua_State* state );
    int lua_error( lua_State* state );
    int lua_sleep( lua_State *state );

    int lua_set_window_title( lua_State* state );
    int lua_set_window_size ( lua_State* state );

} // namespace Arc

#endif // __ARC_SCRIPTING_SYSTEM_H__