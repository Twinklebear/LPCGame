#include <string>
#include <lua.hpp>
#include "src/rect.h"
#include "luacscript.h"
#include "luacrectf.h"

const std::string LuaC::RectfLib::sMetatable = "LPC.Rectf";
const std::string LuaC::RectfLib::sClassName = "Rectf";

int LuaC::RectfLib::luaopen_rectf(lua_State *l){
    return LuaScriptLib::LuaOpenLib(l, sMetatable, sClassName, luaRectfLib, newRectf);
}
void LuaC::RectfLib::addRectf(lua_State *l, int i){
    LuaScriptLib::Add(l, i, sMetatable);
}
Rectf* LuaC::RectfLib::checkRectf(lua_State *l, int i){
    return (Rectf*)luaL_checkudata(l, i, sMetatable.c_str());
}
///The Lua function library struct
const luaL_reg LuaC::RectfLib::luaRectfLib[] = {
    { "pos", getPos },
    { "x", getX },
    { "y", getY },
    { "w", getW },
    { "h", getH },
    { "__newindex", newIndex },
    { "__tostring", toString },
    { "__concat", concat },
    { NULL, NULL}
};
int LuaC::RectfLib::newRectf(lua_State *l){
    return 1;
}
int LuaC::RectfLib::getPos(lua_State *l){
    return 1;
}
int LuaC::RectfLib::getX(lua_State *l){
    return 1;
}
int LuaC::RectfLib::getY(lua_State *l){
    return 1;
}
int LuaC::RectfLib::getW(lua_State *l){
    return 1;
}
int LuaC::RectfLib::getH(lua_State *l){
    return 1;
}
int LuaC::RectfLib::newIndex(lua_State *l){
    return 0;
}
int LuaC::RectfLib::setPos(lua_State *l){
    return 0;
}
int LuaC::RectfLib::setX(lua_State *l){
    return 0;
}
int LuaC::RectfLib::setY(lua_State *l){
    return 0;
}
int LuaC::RectfLib::setW(lua_State *l){
    return 0;
}
int LuaC::RectfLib::setH(lua_State *l){
    return 0;
}
int LuaC::RectfLib::equality(lua_State *l){
    return 1;
}
int LuaC::RectfLib::toString(lua_State *l){
    return 1;
}
int LuaC::RectfLib::concat(lua_State *l){
    return 1;
}