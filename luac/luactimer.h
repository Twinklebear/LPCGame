#ifndef LUACTIMER_H
#define LUACTIMER_H

#include <string>
#include <lua.hpp>
#include "src/timer.h"

///A namespace for storing the Lua C API code
/**
*  A namespace to store the various functions for interacting with
*  Lua via the Lua C API
*/
namespace LuaC {
    /**
    *  The Lua library for the Timer class
    */
    class TimerLib {
    public:
        ///Open the Timer library for Lua state l
        static int luaopen_timer(lua_State *l);
        /**
        *  Add the Timer metatable to the userdata at index i
        *  i is relative to top (ie. -1 is top)
        *  @param l The Lua state
        *  @param i The index of the userdata to add (index relative to top, neg #'s)
        */
        static void addTimer(lua_State *l, int i);
        /**
        *  Check if the userdata at index i in the stack is a Timer
        *  and return a pointer to it
        *  @param l The Lua state
        *  @param i The index of the userdata (standard index, pos #'s)
        */
        static Timer* checkTimer(lua_State *l, int i);

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

    private:
        static const std::string sMetatable, sClassName;
    };
};
#endif