#ifndef LUACRECTF_H
#define LUACRECTF_H

#include <string>
#include <lua.hpp>
#include "luacudata.h"
#include "src/rect.h"

///A namespace for storing the Lua C API code
/**
*  A namespace to store the various functions for interacting with
*  Lua via the Lua C API
*/
namespace LuaC {
    ///The Rectf metatable name
    const std::string rectfMeta = "LPC.Rectf";
    ///The Rectf class/type name
    const std::string rectfClass = "Rectf";
    ///Define Rectf specialization for UdataLib
    template<>
    const std::string UdataLib<Rectf>::mMetaTable = rectfMeta;
    /**
    *  The Lua library for the Rectf class
    */
    class RectfLib : public UdataLib<Rectf> {
    public:
        ///Open the Rectf library for Lua state l
        static int luaopen_rectf(lua_State *l);

    private:
        ///The Lua function library struct
        static const luaL_reg luaRectfLib[];
        ///Make a new Rectf in Lua state l
        static int newRectf(lua_State *l);
        ///Getters
        ///Get the Vector2f pos
        static int getPos(lua_State *l);
        static int getX(lua_State *l);
        static int getY(lua_State *l);
        static int getW(lua_State *l);
        static int getH(lua_State *l);
        ///__newindex accessor for setters
        static int newIndex(lua_State *l);
        ///Setters
        static int setPos(lua_State *l);
        static int setX(lua_State *l);
        static int setY(lua_State *l);
        static int setW(lua_State *l);
        static int setH(lua_State *l);
        ///Operators
        static int equality(lua_State *l);
        static int toString(lua_State *l);
        static int concat(lua_State *l);
        /**
        *  Concatenate a Rectf with a string, a helper for concat fcn
        *  @param l The Lua state
        *  @param rIdx The index of the Rectf in the stack
        *  @para sIdx The index of the string in the stack
        */
        static void concatWithString(lua_State *l, int rIdx, int sIdx);
    };
}

#endif