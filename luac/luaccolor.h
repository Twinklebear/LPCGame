#ifndef LUACCOLOR_H
#define LUACCOLOR_H

#include <string>
#include <lua.hpp>
#include "src/color.h"

///A namespace for storing the Lua C API code
/**
*  A namespace to store the various functions for interacting with
*  Lua via the Lua C API
*/
namespace LuaC {
    ///The Color metatable name
    const std::string colorMeta = "LPC.Color";
    ///The Color class/type name
    const std::string colorClass = "Color";
    /**
    *  The Lua library for the Color class
    */
    class ColorLib {
    public:
        ///Open the Color library for Lua state l
        static int luaopen_color(lua_State *l);
        /**
        *  Add the Color metatable to the userdata at index i
        *  i is relative to top (ie. -1 is top)
        *  @param l The Lua state
        *  @param i The index of the userdata to add (index relative to top, neg #'s)
        */
        static void addColor(lua_State *l, int i);
        /**
        *  Check if the userdata at index i in the stack is a Color
        *  and return a pointer to it
        *  @param l The Lua state
        *  @param i The index of the userdata (standard index, pos #'s)
        */
        static Color* checkColor(lua_State *l, int i);
        /**
        *  Push a Color onto the stack of some Lua state
        *  @param vector The Color to push onto the stack
        *  @param l The Lua State to push onto
        */
        static void PushColor(Color *color, lua_State *l);
        /**
        *  Copy a Color at some index in one Lua state's stack
        *  to the top of some other state's stack
        *  @param from The Lua state to copy the Color from
        *  @param idx The index in the stack of from of the Color
        *  @param too The Lua state to copy the Color into
        */
        static void CopyColor(lua_State *from, int idx, lua_State *too);

    private:
        /**
        *  Allocate memory for a Color on some lua_State and assign it the 
        *  Color metatable
        *  @param l The Lua state to allocate memory on
        *  @return Pointer to the allocated Color
        */
        static Color* AllocateColor(lua_State *l);

    private:
        ///The Lua function library struct
        static const luaL_reg luaColorLib[];
        ///Make a new Color in Lua state l
        static int newColor(lua_State *l);
        ///Getters
        static int getR(lua_State *l);
        static int getG(lua_State *l);
        static int getB(lua_State *l);
        ///Setter
        static int set(lua_State *l);
        ///__newindex for setters
        static int newIndex(lua_State *l);
        ///Setters for __newindex
        static int setR(lua_State *l);
        static int setG(lua_State *l);
        static int setB(lua_State *l);
        ///Operators
        static int equality(lua_State *l);
        static int toString(lua_State *l);
        static int concat(lua_State *l);
        /**
        *  Concatenate a Color with a string, a helper for concat fcn
        *  @param l The Lua state
        *  @param cIdx The index of the Color in the stack
        *  @para sIdx The index of the string in the stack
        */
        static void concatWithString(lua_State *l, int cIdx, int sIdx);

    public:
        ///Meta and Class table names
        static const std::string sMetatable, sClassName;
    };
};

#endif