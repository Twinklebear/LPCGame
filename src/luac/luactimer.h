#ifndef LUACTIMER_H
#define LUACTIMER_H

#include <string>
#include <lua.hpp>
#include "luacdata.h"
#include "core/timer.h"

///A namespace for storing the Lua C API code
/**
*  A namespace to store the various functions for interacting with
*  Lua via the Lua C API
*/
namespace LuaC {
    ///The Timer metatable name
    const std::string timerMeta = "LPC.Timer";
    ///The Timer class/type name
    const std::string timerClass = "Timer";
    ///Define Timer template specialization for UdataLib
    template<>
    const std::string DataLib<Timer>::mMetaTable = timerMeta;
    /**
    *  The Lua library for the Timer class
    */
    class TimerLib : public DataLib<Timer> {
    public:
        ///Open the Timer library for Lua state l
        static int luaopen_timer(lua_State *l);

    private:
        ///The Lua function library struct
        static const luaL_reg luaTimerLib[];
        ///Make a new Timer in Lua state l
        static int newTimer(lua_State *l);
        static int start(lua_State *l);
        static int stop(lua_State *l);
        static int pause(lua_State *l);
        static int unpause(lua_State *l);
        static int restart(lua_State *l);
        static int ticks(lua_State *l);
        ///Getters
        static int started(lua_State *l);
        static int paused(lua_State *l);
    };
};
#endif