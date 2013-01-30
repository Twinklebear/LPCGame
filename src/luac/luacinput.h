#ifndef LUACINPUT_H
#define LUACINPUT_H

#include <string>
#include <lua.hpp>
#include "core/input.h"

///A namespace for storing the Lua C API code
/**
*  A namespace to store the various functions for interacting with
*  Lua via the Lua C API
*/
namespace LuaC {
    ///The Input class/type name
    const std::string inputClass = "Input";
    /**
    *  The Lua library for the Debug class
    */
    class InputLib {
    public:
        ///Open the Input library
        static int luaopen_input(lua_State *l);

    private:
        ///The Lua function library
        static const struct luaL_reg luaInputLib[];
        ///Setup the SDL_SCANCODE enum
        static void openKeyEnum(lua_State *l);
        ///Setup the SDL_HAT enum
        static void openHatEnum(lua_State *l);
        static int keyDown(lua_State *l);
        static int joystickAvailable(lua_State *l);
        static int getJoyAxis(lua_State *l);
        static int getJoyButtonDown(lua_State *l);
        static int getJoyHat(lua_State *l);
        static int joySupportsHaptic(lua_State *l);
        static int getQuit(lua_State *l);
        static int getMousePos(lua_State *l);
    };
}

#endif