#ifndef LUACPHYSICS_H
#define LUACPHYSICS_H

#include <string>
#include <lua.hpp>
#include "src/physics.h"

///A namespace for storing the Lua C API code
/**
*  A namespace to store the various functions for interacting with
*  Lua via the Lua C API
*/
namespace LuaC {
    /**
    *  The Lua library for the Physics class
    */
    class PhysicsLib {
    public:
        ///Open the Physics library for Lua state l
        static int luaopen_physics(lua_State *l);
        /**
        *  Add the Physics metatable to the userdata at index i
        *  i is relative to top (ie. -1 is top)
        *  @param l The Lua state
        *  @param i The index of the userdata to add (index relative to top, neg #'s)
        */
        static void addPhysics(lua_State *l, int i);
        /**
        *  Check if the userdata at index i in the stack is a Physics
        *  and return a pointer to it
        *  @param l The Lua state
        *  @param i The index of the userdata (standard index, pos #'s)
        */
        static Physics** checkPhysics(lua_State *l, int i);

    private:
        ///The Lua function library
        static const struct luaL_reg luaPhysicsLib[];
        ///Getters
        static int position(lua_State *l);
        static int velocity(lua_State *l);
        static int acceleration(lua_State *l);
        static int box(lua_State *l);
        static int state(lua_State *l);
        ///__newindex accessor
        static int accessor(lua_State *l);
        ///Setters
        static int setPosition(lua_State *l);
        static int setVelocity(lua_State *l);
        static int setAcceleration(lua_State *l);
        static int setHorizDir(lua_State *l);
        static int setVertDir(lua_State *l);
        static int setBox(lua_State *l);
        ///Operators
        static int toString(lua_State *l);
        static int concat(lua_State *l);

    public:
        static const std::string sMetatable, sClassName;
    };
};

#endif