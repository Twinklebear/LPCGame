#ifndef LUACPHYSICS_H
#define LUACPHYSICS_H

#include <string>
#include <memory>
#include <lua.hpp>
#include "src/physics.h"

///A namespace for storing the Lua C API code
/**
*  A namespace to store the various functions for interacting with
*  Lua via the Lua C API
*/
namespace LuaC {
    ///The Physics metatable name
    const std::string physicsMeta = "LPC.Physics";
    ///The Physics class/type name
    const std::string physicsClass = "Physics";
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
        static std::weak_ptr<Physics>* checkPhysics(lua_State *l, int i);
        /**
        *  Push a Physics onto the stack of some Lua state
        *  @param physics The Physics to push onto the stack
        *  @param l The Lua State to push onto
        */
        static void PushPhysics(std::weak_ptr<Physics> *physics, lua_State *l);
        /**
        *  Copy a Physics at some index in one Lua state's stack
        *  to the top of some other state's stack
        *  @param from The Lua state to copy the Physics from
        *  @param idx The index in the stack of from of the Physics
        *  @param too The Lua state to copy the Physics into
        */
        static void CopyPhysics(lua_State *from, int idx, lua_State *too);
        /**
        *  Allocate memory for a Physics on some lua_State and assign it the 
        *  Physics metatable
        *  @param l The Lua state to allocate memory on
        *  @return Pointer to the allocated Physics
        */
        static std::weak_ptr<Physics>* AllocatePhysics(lua_State *l);

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