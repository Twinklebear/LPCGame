#ifndef LUACDEBUG_H
#define LUACDEBUG_H

#include <string>
#include <lua.hpp>
#include "src/debug.h"

///A namespace for storing the Lua C API code
/**
*  A namespace to store the various functions for interacting with
*  Lua via the Lua C API
*/
namespace LuaC {
    /**
    *  The Lua library for the Debug class
    */
    class DebugLib {
    public:
        ///Open the Debug library
        static int luaopen_debug(lua_State *l);

    private:
        ///The Lua function library
        static const struct luaL_reg luaDebugLib[];
        ///For writing to the debug log
        static int log(lua_State *l);

    private:
        static const std::string sClassName;
    };
};
#endif