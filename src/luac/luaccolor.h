#ifndef LUACCOLOR_H
#define LUACCOLOR_H

#include <string>
#include <lua.hpp>
#include "luacdata.h"
#include "core/color.h"

///A namespace for storing the Lua C API code
/**
*  A namespace to store the various functions for interacting with
*  Lua via the Lua C API
*/
namespace LuaC {
    ///The Color class/type name
    const std::string colorClass = "Color";
    template<>
    const std::string DataLib<Color>::mMetaTable = "LPC.Color";
    /**
    *  The Lua library for the Color class
    */
    class ColorLib : public DataLib<Color> {
    public:
        ///Open the Color library for Lua state l
        static int luaopen_color(lua_State *l);

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
    };
}

#endif