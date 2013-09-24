#include "ScriptingSystem.h"
#include "Program.h"
#include "GraphicsSystem.h"

Arc::ScriptingSystem::ScriptingSystem( void )
{
    _pLuaState = luaL_newstate();

    luaL_openlibs(_pLuaState);

    registerFunctions();
}

Arc::ScriptingSystem::~ScriptingSystem( void )
{
    lua_close(_pLuaState);
}

void Arc::ScriptingSystem::executeFile( string filename )
{
    int status = luaL_loadfile(_pLuaState, filename.c_str());

    if (status == 0)
    {
        status = lua_pcall(_pLuaState, 0, LUA_MULTRET, 0);
    }

    showErrors(status);
}

void Arc::ScriptingSystem::showErrors( int status )
{
    if (status != 0)
    {
        ERRORF(toString(), "%s", lua_tostring(_pLuaState, -1));
        lua_pop(_pLuaState, 1); // remove error message
    }
}

void Arc::ScriptingSystem::registerFunctions( void )
{
    lua_register(_pLuaState, "arc_die",   lua_die);
    lua_register(_pLuaState, "arc_info",  lua_info);
    lua_register(_pLuaState, "arc_error", lua_error);
    lua_register(_pLuaState, "arc_sleep", lua_sleep);

    lua_register(_pLuaState, "arc_set_window_size",  lua_set_window_size);
    lua_register(_pLuaState, "arc_set_window_title", lua_set_window_title);
}

int Arc::lua_die( lua_State* state )
{
    int argc = lua_gettop(state);

    int errorLevel = (argc == 0 ? 0 : lua_tointeger(state, 1));
    die(errorLevel);

    return 0;
}

int Arc::lua_info( lua_State* state )
{
    int argc = lua_gettop(state);

    if (argc > 0)
    {
        INFO("Lua", lua_tostring(state, 1));
    }

    return 0;
}

int Arc::lua_error( lua_State* state )
{
    int argc = lua_gettop(state);

    if (argc > 0)
    {
        ERROR("Lua", lua_tostring(state, 1));
    }

    return 0;
}

int Arc::lua_sleep( lua_State *state )
{
    int argc = lua_gettop(state);

    if (argc > 0)
    {
        int millis = lua_tointeger(state, 1);
        Timer timer;
        timer.start();
        timer.sleepUntilElapsed(millis);
    }

    return 0;
}

int Arc::lua_set_window_title( lua_State* state )
{
    int argc = lua_gettop(state);
    GraphicsSystem* gs = Program::getInstance()->getGraphicsSystem();

    if (argc > 0)
    {
        gs->setWindowTitle(lua_tostring(state, 1));
    }

    return 0;
}

int Arc::lua_set_window_size( lua_State* state )
{
    int argc = lua_gettop(state);
    GraphicsSystem* gs = Program::getInstance()->getGraphicsSystem();

    if (argc >= 2)
    {
        gs->setWindowSize(Size((float)lua_tointeger(state, 1), (float)lua_tointeger(state, 2)));
    }

    return 0;
}
