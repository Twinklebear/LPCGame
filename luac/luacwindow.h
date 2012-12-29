#ifndef LUACWINDOW_H
#define LUACWINDOW_H

#include <string>
#include <lua.hpp> 

///A namespace for storing the Lua C API code
/**
*  A namespace to store the various functions for interacting with
*  Lua via the Lua C API
*/
namespace LuaC {
    //The Window class/type name
    const std::string windowClass = "Window";
    /**
    *  The Lua library for the Window class
    */
    class WindowLib {
    public:
        ///Open the Window library
        static int luaopen_window(lua_State *l);

    private:
        ///The Lua function library
        static const struct luaL_reg luaWindowLib[];
        /**
        *  Draw something to the screen, this function deduces 
        *  the parameters and calls the appropriate function
        */
        static int draw(lua_State *l);
        ///Get the window's box
        static int getBox(lua_State *l);

    private:
        ///The functions called when resolving draw parameters
        static void DrawImage(lua_State *l);
        static void DrawAnimatedImage(lua_State *l);
        static void DrawText(lua_State *l);
    };
}

#endif