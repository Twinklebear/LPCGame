#include <string>
#include <lua.hpp>
#include "src/rect.h"
#include "luacscript.h"
#include "luacvector2f.h"
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
    //Stack: table (Rectf), params if desired
    bool initVals = (lua_gettop(l) == 5);
    Rectf *r = (Rectf*)lua_newuserdata(l, sizeof(Rectf));
    if (initVals)
        r->Set(luaL_checknumber(l, 2), luaL_checknumber(l, 3),
            luaL_checknumber(l, 4), luaL_checknumber(l, 5));
    else
        r->Set(0, 0, 0, 0);
    addRectf(l, -1);
    return 1;
}
int LuaC::RectfLib::getPos(lua_State *l){
    //Stack: userdata (Rectf)
    Rectf *r = checkRectf(l, 1);
    //Make a new vector2f
    Vector2f *v = (Vector2f*)lua_newuserdata(l, sizeof(Vector2f));
    //Register the vector with the metatable

    v->Set(r->pos);
    return 1;
}
int LuaC::RectfLib::getX(lua_State *l){
    //Stack: userdata (Rectf)
    Rectf *r = checkRectf(l, 1);
    lua_pushnumber(l, r->X());
    return 1;
}
int LuaC::RectfLib::getY(lua_State *l){
    //Stack: userdata (Rectf)
    Rectf *r = checkRectf(l, 1);
    lua_pushnumber(l, r->Y());
    return 1;
}
int LuaC::RectfLib::getW(lua_State *l){
    //Stack: userdata (Rectf)
    Rectf *r = checkRectf(l, 1);
    lua_pushnumber(l, r->W());
    return 1;
}
int LuaC::RectfLib::getH(lua_State *l){
    //Stack: userdata (Rectf)
    Rectf *r = checkRectf(l, 1);
    lua_pushnumber(l, r->H());
    return 1;
}
int LuaC::RectfLib::newIndex(lua_State *l){
    //Stack: udata, string of index to set, val to set
    //Get the index to set "x", "y", so on and then remove it
    std::string val = luaL_checkstring(l, 2);
    lua_remove(l, 2);
    //Stack: udata, val to set
    switch (val.at(0)){
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
    //Stack: userdata (Rectf), userdata (Vector2f)
    Rectf *r = checkRectf(l, 1);
    Vector2f *v = nullptr; //Vector2fLib::checkVector2f(l, 2);
    r->Set(*v);
    return 0;
}
int LuaC::RectfLib::setX(lua_State *l){
    //Stack: userdata (Rectf), number
    Rectf *r = checkRectf(l, 1);
    r->Set(luaL_checknumber(l, 2), r->Y());
    return 0;
}
int LuaC::RectfLib::setY(lua_State *l){
    //Stack: userdata (Rectf), number
    Rectf *r = checkRectf(l, 1);
    r->Set(r->X(), luaL_checknumber(l, 2));
    return 0;
}
int LuaC::RectfLib::setW(lua_State *l){
    //Stack: userdata (Rectf), number
    Rectf *r = checkRectf(l, 1);
    r->Set(r->X(), r->Y(), luaL_checknumber(l, 2), r->H());
    return 0;
}
int LuaC::RectfLib::setH(lua_State *l){
    //Stack: userdata (Rectf), number
    Rectf *r = checkRectf(l, 1);
    r->Set(r->X(), r->Y(), r->W(), luaL_checknumber(l, 2));
    return 0;
}
int LuaC::RectfLib::equality(lua_State *l){
    //Stack: userdata (Rectf), userdata (Rectf)
    Rectf *r1 = checkRectf(l, 1);
    Rectf *r2 = checkRectf(l, 2);
    lua_pushboolean(l, (r1->X() == r2->X() && r1->Y() == r2->Y()
                     && r1->W() == r2->W() && r1->H() == r2->H()));
    return 1;
}
int LuaC::RectfLib::toString(lua_State *l){
    //Need std::string conversion in rect
    return 1;
}
int LuaC::RectfLib::concat(lua_State *l){
    //Need std::string conversion in rect
    return 1;
}