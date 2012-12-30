#ifndef LUACVECTOR2F_H
#define LUACVECTOR2F_H

#include <string>
#include <lua.hpp>
#include "luacudata.h"
#include "src/vectors.h"

///A namespace for storing the Lua C API code
/**
*  A namespace to store the various functions for interacting with
*  Lua via the Lua C API
*/
namespace LuaC {
    ///The Vector2f metatable name
    const std::string vector2fMeta = "LPC.Vector2f";
    ///The Vector2f class/type name
    const std::string vector2fClass = "Vector2f";
    ///Define Vector2f specialization for UdataLib
    template<>
    const std::string UdataLib<Vector2f>::mMetaTable = vector2fMeta;
    /**
    *  The Lua library for the Vector2f class
    */
    class Vector2fLib : public UdataLib<Vector2f> {
    public:
        ///Open the Vector2f library for Lua state l
        static int luaopen_vector2f(lua_State *l);

    private:
        //The Lua Functions
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
        *  Multiply a Vector2f by a float, a helper for multiplication fcn
        *  @param l The Lua state
        *  @param vIdx The index of the Vector2f in the stack
        *  @param fIdx The index of the float in the stack
        */
        static void multWithFloat(lua_State *l, int vIdx, int fIdx);
        static int division(lua_State *l);
        static int toString(lua_State *l);
        static int concat(lua_State *l);
        /**
        *  Concatenate a Vector2f with a string, a helper for concat fcn
        *  @param l The Lua state
        *  @param vIdx The index of the Vector2f in the stack
        *  @param sIdx The index of the string in the stack
        */
        static void concatWithString(lua_State *l, int vIdx, int sIdx);
    };
}

#endif