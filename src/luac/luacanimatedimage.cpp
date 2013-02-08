#include <string>
#include <memory>
#include <lua.hpp>
#include "luacscript.h"
#include "luacrectf.h"
#include "core/animatedimage.h"
#include "luacanimatedimage.h"

int LuaC::AnimatedImageLib::luaopen_animatedimage(lua_State *l){
    return LuaScriptLib::LuaOpenLib(l, animatedImageMeta, animatedImageClass, 
        luaAnimatedImageLib, newAnimatedImage);
}
const struct luaL_reg LuaC::AnimatedImageLib::luaAnimatedImageLib[] = {
    { "update", update },
    { "play", play },
    { "playing", playing },
    { "size", size },
    { "w", width },
    { "h", height },
    { "file", file },
    { "release", release },
    { "__gc", garbageCollection },
    { NULL, NULL }
};
int LuaC::AnimatedImageLib::newAnimatedImage(lua_State *l){
    //Stack: class table, file name
    std::string file = luaL_checkstring(l, 2);
    Push(l, std::make_shared<AnimatedImage>(file));
    return 1;
}
int LuaC::AnimatedImageLib::update(lua_State *l){
    //Stack: animated image
    std::shared_ptr<AnimatedImage> *img = Check(l, 1);
    (*img)->Update();
    return 0;
}
int LuaC::AnimatedImageLib::play(lua_State *l){
    //Stack: animated image, name of sequence to play
    std::shared_ptr<AnimatedImage> *img = Check(l, 1);
    std::string name = luaL_checkstring(l, 2);
    (*img)->Play(name);
    return 0;
}
int LuaC::AnimatedImageLib::playing(lua_State *l){
    //Stack: animated image
    std::shared_ptr<AnimatedImage> *img = Check(l, 1);
    lua_pushstring(l, (*img)->Playing().c_str());
    return 1;
}
int LuaC::AnimatedImageLib::size(lua_State *l){
    //Stack: animated image
    std::shared_ptr<AnimatedImage> *img = Check(l, 1);
    lua_pushinteger(l, (*img)->W());
    lua_pushinteger(l, (*img)->H());
    return 2;
}
int LuaC::AnimatedImageLib::width(lua_State *l){
    //Stack: animated image
    std::shared_ptr<AnimatedImage> *img = Check(l, 1);
    lua_pushinteger(l, (*img)->W());
    return 1;
}
int LuaC::AnimatedImageLib::height(lua_State *l){
    //Stack: animated image
    std::shared_ptr<AnimatedImage> *img = Check(l, 1);
    lua_pushinteger(l, (*img)->H());
    return 1;
}
int LuaC::AnimatedImageLib::file(lua_State *l){
    //Stack: animated image
    std::shared_ptr<AnimatedImage> *img = Check(l, 1);
    lua_pushstring(l, (*img)->File().c_str());
    return 1;
}
int LuaC::AnimatedImageLib::release(lua_State *l){
    //Stack: animated image
    std::shared_ptr<AnimatedImage> *img = Check(l, 1);
    img->~shared_ptr();
    return 0;
}
int LuaC::AnimatedImageLib::garbageCollection(lua_State *l){
    return release(l);
}
