#ifndef LUACRECTF_H
#define LUACRECTF_H

#include <string>
#include <lua.hpp>
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
    /**
    *  The Lua library for the Rectf class
    */
    class RectfLib {
    public:
        ///Open the Rectf library for Lua state l
        static int luaopen_rectf(lua_State *l);
        /**
        *  Add the Rectf metatable to the userdata at index i
        *  i is relative to top (ie. -1 is top)
        *  @param l The Lua state
        *  @param i The index of the userdata to add (index relative to top, neg #'s)
        */
        static void addRectf(lua_State *l, int i);
        /**
        *  Check if the userdata at index i in the stack is a Rectf
        *  and return a pointer to it
        *  @param l The Lua state
        *  @param i The index of the userdata (standard index, pos #'s)
        */
        static Rectf* checkRectf(lua_State *l, int i);
        /**
        *  Push a Rectf onto the stack of some Lua state
        *  @param rect The Rectf to push onto the stack
        *  @param l The Lua State to push onto
        */
        static void PushRectf(Rectf *rect, lua_State *l);
        /**
        *  Copy a Rectf at some index in one Lua state's stack
        *  to the top of some other state's stack
        *  @param from The Lua state to copy the Rectf from
        *  @param idx The index in the stack of from of the Rectf
        *  @param too The Lua state to copy the Rectf into
        */
        static void CopyRectf(lua_State *from, int idx, lua_State *too);
        /**
        *  Allocate memory for a Rectf on some lua_State and assign it the 
        *  Rectf metatable
        *  @param l The Lua state to allocate memory on
        *  @return Pointer to the allocated Rectf
        */
        static Rectf* AllocateRectf(lua_State *l);

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