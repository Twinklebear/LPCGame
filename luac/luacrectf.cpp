#include <string>
#include <lua.hpp>
#include "src/rect.h"
#include "luacscript.h"
#include "luacvector2f.h"
#include "luacrectf.h"

int LuaC::RectfLib::luaopen_rectf(lua_State *l){
    return LuaScriptLib::LuaOpenLib(l, rectfMeta, rectfClass, luaRectfLib, newRectf);
}
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
    //Stack: table (Rectf), params if desired
    bool initVals = (lua_gettop(l) == 5);
    Rectf *r = Allocate(l);
    if (initVals)
        r->Set(luaL_checknumber(l, 2), luaL_checknumber(l, 3),
            luaL_checknumber(l, 4), luaL_checknumber(l, 5));

    return 1;
}
int LuaC::RectfLib::getPos(lua_State *l){
    //Stack: userdata (Rectf)
    Rectf *r = Check(l, 1);
    Vector2fLib::Push(&r->pos, l);
    return 1;
}
int LuaC::RectfLib::getX(lua_State *l){
    //Stack: userdata (Rectf)
    Rectf *r = Check(l, 1);
    lua_pushnumber(l, r->X());
    return 1;
}
int LuaC::RectfLib::getY(lua_State *l){
    //Stack: userdata (Rectf)
    Rectf *r = Check(l, 1);
    lua_pushnumber(l, r->Y());
    return 1;
}
int LuaC::RectfLib::getW(lua_State *l){
    //Stack: userdata (Rectf)
    Rectf *r = Check(l, 1);
    lua_pushnumber(l, r->W());
    return 1;
}
int LuaC::RectfLib::getH(lua_State *l){
    //Stack: userdata (Rectf)
    Rectf *r = Check(l, 1);
    lua_pushnumber(l, r->H());
    return 1;
}
int LuaC::RectfLib::newIndex(lua_State *l){
    //Stack: udata, string of index to set, val to set
    //Get the index to set "x", "y", so on and then remove it
    std::string index = luaL_checkstring(l, 2);
    LuaScriptLib::StackDump(l);
    switch (index.at(0)){
        case 'x':
            return setX(l);
        case 'y':
            return setY(l);
        case 'w':
            return setW(l);
        case 'h':
            return setH(l);
        case 'p':
            return setPos(l);
        default:
            break;
    }
    return 0;
}
int LuaC::RectfLib::setPos(lua_State *l){
    //Stack: userdata (Rectf), string of index to set, userdata (Vector2f)
    Rectf *r = Check(l, 1);
    Vector2f *v = Vector2fLib::Check(l, 3);
    r->Set(*v);
    return 0;
}
int LuaC::RectfLib::setX(lua_State *l){
    //Stack: userdata (Rectf), string of index to set, number
    Rectf *r = Check(l, 1);
    r->Set(luaL_checknumber(l, 3), r->Y());
    return 0;
}
int LuaC::RectfLib::setY(lua_State *l){
    //Stack: userdata (Rectf), string of index to set, number
    Rectf *r = Check(l, 1);
    r->Set(r->X(), luaL_checknumber(l, 3));
    return 0;
}
int LuaC::RectfLib::setW(lua_State *l){
    //Stack: userdata (Rectf), string of index to set, number
    Rectf *r = Check(l, 1);
    r->Set(r->X(), r->Y(), luaL_checknumber(l, 3), r->H());
    return 0;
}
int LuaC::RectfLib::setH(lua_State *l){
    //Stack: userdata (Rectf), string of index to set, number
    Rectf *r = Check(l, 1);
    r->Set(r->X(), r->Y(), r->W(), luaL_checknumber(l, 3));
    return 0;
}
int LuaC::RectfLib::equality(lua_State *l){
    //Stack: userdata (Rectf), userdata (Rectf)
    Rectf *r1 = Check(l, 1);
    Rectf *r2 = Check(l, 2);
    lua_pushboolean(l, *r1 == *r2);
    return 1;
}
int LuaC::RectfLib::toString(lua_State *l){
    //Stack: userdata (Rectf)
    Rectf *r = Check(l, 1);
    lua_pushstring(l, ((std::string)(*r)).c_str());
    return 1;
}
int LuaC::RectfLib::concat(lua_State *l){
    /*
    *  Stack has 2 possible configs
    *  1. string, userdata (Rectf)
    *  2. userdata (Rectf), string
    */
    if (lua_type(l, 1) == LUA_TSTRING)
        concatWithString(l, 2, 1);
    else
        concatWithString(l, 1, 2);
    return 1;
}
void LuaC::RectfLib::concatWithString(lua_State *l, int rIdx, int sIdx){
    //Stack: userdata (Rectf) @ rIdx, string @ sIdx
    Rectf *r = Check(l, rIdx);
    std::string s = luaL_checkstring(l, sIdx);
    //Add the strings with the proper ordering
    if (rIdx < sIdx)
        lua_pushstring(l, ((std::string)(*r) + s).c_str());
    else
        lua_pushstring(l, (s + (std::string)(*r)).c_str());
}
