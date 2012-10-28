#ifndef LUACSTATE_H
#define LUACSTATE_H

#include <string>
#include <lua.hpp>
#include "src/statemanager.h"
#include "src/state.h"

///A namespace for storing the Lua C API code
/**
*  A namespace to store the various functions for interacting with
*  Lua via the Lua C API
*/
namespace LuaC {
    /**
    *  The Lua library for the State class
    *  Allows for interaction with the active State via the Statemanager
    */
    class StateLib {
    public:
        ///Open the State library for Lua state l
        static int luaopen_state(lua_State *l);

    private:
        ///The Lua function library struct
        static const luaL_reg luaStateLib[];
        ///The various Lua function wrappers
        static int getEntity(lua_State *l);
        static int setExit(lua_State *l);
        static int getName(lua_State *l);

    public:
        static const std::string sClassName;
    };
};

#endif