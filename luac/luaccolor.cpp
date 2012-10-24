#include <string>
#include <lua.hpp>
#include "src/color.h"
#include "luacscript.h"
#include "luaccolor.h"

const std::string LuaC::ColorLib::sMetatable = "LPC.Color";
const std::string LuaC::ColorLib::sClassName = "Color";

int LuaC::ColorLib::luaopen_color(lua_State *l){
    return LuaScriptLib::LuaOpenLib(l, sMetatable, sClassName, luaColorLib, newColor);
}
void LuaC::ColorLib::addColor(lua_State *l, int i){
    LuaScriptLib::Add(l, i, sMetatable);
}
Color* LuaC::ColorLib::checkColor(lua_State *l, int i){
    return (Color*)luaL_checkudata(l, i, sMetatable.c_str());
}
const luaL_reg LuaC::ColorLib::luaColorLib[] = {
    { "r", getR },
    { "g", getG },
    { "b", getB },
    { "set", set },
    { "__newindex", newIndex },
    { "__eq", equality },
    { "__tostring", toString },
    { "__concat", concat },
    { NULL, NULL }
};
int LuaC::ColorLib::newColor(lua_State *l){
    //Stack: table (Color), vals for r, g, b if desired
    bool initVals = (lua_gettop(l) == 4);
    Color *c = (Color*)lua_newuserdata(l, sizeof(Color));
    if (initVals)
        c->Set(luaL_checkint(l, 2), luaL_checkint(l, 3), luaL_checkint(l, 4));
    else
        c->Set(0, 0, 0);
    addColor(l, -1);
    return 1;
}
int LuaC::ColorLib::getR(lua_State *l){
    //Stack: userdata (Color)
    Color *c = checkColor(l, 1);
    lua_pushinteger(l, c->R());
    return 1;
}
int LuaC::ColorLib::getG(lua_State *l){
    //Stack: userdata (Color)
    Color *c = checkColor(l, 1);
    lua_pushinteger(l, c->G());
    return 1;
}
int LuaC::ColorLib::getB(lua_State *l){
    //Stack: userdata (Color)
    Color *c = checkColor(l, 1);
    lua_pushinteger(l, c->B());
    return 1;
}
int LuaC::ColorLib::set(lua_State *l){
    //Stack: userdata (Color), vals for r, g, b
    Color *c = checkColor(l, 1);
    c->Set(luaL_checkint(l, 2), luaL_checkint(l, 3), luaL_checkint(l, 4));
    return 0;
}
int LuaC::ColorLib::newIndex(lua_State *l){
    //Stack: userdata (Color), string of index to set, val for index
    std::string index = luaL_checkstring(l, 2);
    lua_remove(l, 2);
    switch (index.at(0)){
        case 'r':
            return setR(l);
        case 'g':
            return setG(l);
        case 'b':
            return setB(l);
        default:
            break;
    }
    return 0;
}
int LuaC::ColorLib::setR(lua_State *l){
    //Stack: userdata (Color), val for R
    Color *c = checkColor(l, 1);
    c->R(luaL_checkint(l, 2));
    return 0;
}
int LuaC::ColorLib::setG(lua_State *l){
    //Stack: userdata (Color), val for G
    Color *c = checkColor(l, 1);
    c->G(luaL_checkint(l, 2));
    return 0;
}
int LuaC::ColorLib::setB(lua_State *l){
    //Stack: userdata (Color), val for B
    Color *c = checkColor(l, 1);
    c->B(luaL_checkint(l, 2));
    return 0;
}
int LuaC::ColorLib::equality(lua_State *l){
    //Stack: userdata (Color), userdata (Color)
    Color *c1 = checkColor(l, 1);
    Color *c2 = checkColor(l, 2);
    lua_pushboolean(l, *c1 == *c2);
    return 1;
}
int LuaC::ColorLib::toString(lua_State *l){
    //Stack: userdata (Color)
    Color *c = checkColor(l, 1);
    lua_pushstring(l, ((std::string)(*c)).c_str());
    return 1;
}
int LuaC::ColorLib::concat(lua_State *l){
    /*
    *  Stack has 2 possible configurations
    *  1. string, userdata (Color)
    *  2. userdata (Color), string
    */
    if (lua_type(l, 1) == LUA_TSTRING)
        concatWithString(l, 2, 1);
    else
        concatWithString(l, 1, 2);
    return 1;
}
void LuaC::ColorLib::concatWithString(lua_State *l, int cIdx, int sIdx){
    //Stack: userdata (Color) @ cIdx, string @ sIdx
    Color *c = checkColor(l, cIdx);
    std::string s = luaL_checkstring(l, sIdx);
    //Add the strings with proper ordering
    if (cIdx < sIdx)
        lua_pushstring(l, ((std::string)(*c) + s).c_str());
    else
        lua_pushstring(l, (s + (std::string)(*c)).c_str());
}
