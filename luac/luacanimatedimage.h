#ifndef LUAC_ANIMATEDIMAGE_H
#define LUAC_ANIMATEDIMAGE_H

#include <string>
#include <memory>
#include <lua.hpp>
#include "luacudata.h"
#include "src/animatedimage.h"

///A namespace for storing the Lua C API code
/**
*  A namespace to store the various functions for interacting with
*  Lua via the Lua C API
*/
namespace LuaC {
    ///The Vector2f metatable name
    const std::string animatedImageMeta = "LPC.AnimatedImage";
    ///The Vector2f class/type name
    const std::string animatedImageClass = "AnimatedImage";
    ///Define Vector2f specialization for UdataLib
    template<>
    const std::string UdataLib<std::shared_ptr<AnimatedImage>>::mMetaTable = animatedImageMeta;
    /**
    *  The Lua library for the AnimatedImage class
    */
    class AnimatedImageLib : public UdataLib<std::shared_ptr<AnimatedImage>> {
    public:
        ///Open the Animated Image library in Lua state l
        static int luaopen_animatedimage(lua_State *l);

    private:
        ///The Lua function library
        static const struct luaL_Reg luaAnimatedImageLib[];
        ///Make a new AnimatedImage in Lua state l
        static int newAnimatedImage(lua_State *l);
        ///Update the Animation frame
        static int update(lua_State *l);
        ///Play a desired animation
        static int play(lua_State *l);
        ///Check which animation sequence is playing
        static int playing(lua_State *l);
    };
}

#endif