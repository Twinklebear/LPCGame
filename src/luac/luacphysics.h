#ifndef LUACPHYSICS_H
#define LUACPHYSICS_H

#include <string>
#include <memory>
#include <lua.hpp>
#include "luacdata.h"
#include "core/physics.h"

///A namespace for storing the Lua C API code
/**
*  A namespace to store the various functions for interacting with
*  Lua via the Lua C API
*/
namespace LuaC {
    ///The Physics class/type name
    const std::string physicsClass = "Physics";
    /**
    *  The Lua library for the Physics class
    */
    class PhysicsLib : public DataLib<std::weak_ptr<Physics>> {
    public:
        ///Open the Physics library for Lua state l
        static int luaopen_physics(lua_State *l);

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
    };
}

#endif