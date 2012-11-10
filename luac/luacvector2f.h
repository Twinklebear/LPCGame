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
    ///The Vector2f metatable name
    const std::string vector2fMeta = "LPC.Vector2f";
    ///The Vector2f class/type name
    const std::string vector2fClass = "Vector2f";
    /**
    *  The Lua library for the Vector2f class
    */
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
        /**
        *  Push a Vector2f onto the stack of some Lua state
        *  @param vector The Vector2f to push onto the stack
        *  @param l The Lua State to push onto
        */
        static void PushVector2f(Vector2f *vector, lua_State *l);
        /**
        *  Copy a Vector2f at some index in one Lua state's stack
        *  to the top of some other state's stack
        *  @param from The Lua state to copy the Vector2f from
        *  @param idx The index in the stack of from of the Vector2f
        *  @param too The Lua state to copy the Vector2f into
        */
        static void CopyVector2f(lua_State *from, int idx, lua_State *too);
        
    private:
        /**
        *  Allocate memory for a Vector2f on some lua_State and assign it the 
        *  Vector2f metatable
        *  @param l The Lua state to allocate memory on
        *  @return Pointer to the allocated Vector2f
        */
        static Vector2f* AllocateVector2f(lua_State *l);

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
};

#endif