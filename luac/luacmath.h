#ifndef LUACMATH_H
#define LUACMATH_H

#include <string>
#include <lua.hpp>
#include "src/math.h"

///A namespace for storing the Lua C API code
/**
*  A namespace to store the various functions for interacting with
*  Lua via the Lua C API
*/
namespace LuaC {
    ///The Math class/type name
    const std::string mathClass = "Math";
    /**
    *  The Lua library for the Math class
    */
    class MathLib {
    public:
        ///Open the Math library
        static int luaopen_math(lua_State *l);

    private:
        ///The Lua function library
        static const struct luaL_reg luaMathLib[];
        ///Expose the direction enum
        static void openDirEnum(lua_State *l);
        //The various library functions
        static int distance(lua_State *l);
        static int clamp(lua_State *l);
        static int magnitude(lua_State *l);
        static int normalize(lua_State *l);
        static int lerp(lua_State *l);
        static int forwardVector(lua_State *l);
        static int rectNearRect(lua_State *l);
        static int checkCollision(lua_State *l);
        static int toSceneSpace(lua_State *l);
        static int fromSceneSpace(lua_State *l);
    };
}

#endif