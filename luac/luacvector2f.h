#ifndef LUACVECTOR2F_H
#define LUACVECTOR2F_H

#include <string>
#include <lua.hpp>
#include "src/vectors.h"

///A namespace for storing the Lua C API code
/**
*  A namespace to store the various functions for interacting with
*  Lua via the Lua C API
*/
namespace LuaC {
    class Vector2fLib {
    public:
        ///Open the Vector2f library for Lua state l
        static int luaopen_vector2f(lua_State *l);
        /**
        *  Add the Vector2f metatable to the userdata at index i
        *  i is relative to top (ie. -1 is top)
        *  @param l The Lua state
        *  @param i The index of the userdata to add (index relative to top, neg #'s)
        */
        static void addVector2f(lua_State *l, int i);
        /**
        *  Check if the userdata at index i in the stack is a Vector2f
        *  and return a pointer to it
        *  @param l The Lua state
        *  @param i The index of the userdata (standard index, pos #'s)
        */
        static Vector2f* checkVector2f(lua_State *l, int i);

    private:
        ///The Lua function library struct
        static const luaL_reg luaVector2fLib[];
        ///Make a new Vector2f in Lua State l
        static int newVector2f(lua_State *l);
        ///Getters
        static int getX(lua_State *l);
        static int getY(lua_State *l);
        ///__newindex accessor for setters
        static int newIndex(lua_State *l);
        ///Setters
        static int set(lua_State *l);
        static int setX(lua_State *l);
        static int setY(lua_State *l);
        ///Operators
        static int equality(lua_State *l);
        static int addition(lua_State *l);
        static int subtraction(lua_State *l);
        static int multiplication(lua_State *l);
        /**
        *  Multiply a Vector2f by a float, only used as a helper for
        *  multiplacation function
        *  @param l The Lua state
        *  @param vIdx The index of the Vector2f in the stack
        *  @param fIdx The index of the float in the stack
        */
        static void multVectorWithFloat(lua_State *l, int vIdx, int fIdx);
        static int division(lua_State *l);
        static int toString(lua_State *l);
        static int concat(lua_State *l);

    private:
        ///Meta and Class table names
        static const std::string sMetatable, sClassName;
    };
};

#endif