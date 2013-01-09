#include <string>
#include <lua.hpp>
#include "src/vectors.h"
#include "luacscript.h"
#include "luacvector2f.h"

int LuaC::Vector2fLib::luaopen_vector2f(lua_State *l){
    return LuaScriptLib::LuaOpenLib(l, vector2fMeta, vector2fClass, luaVector2fLib, newVector2f);
}
const luaL_reg LuaC::Vector2fLib::luaVector2fLib[] = {
    { "x", getX },
    { "y", getY },
    { "__newindex", newIndex },
    { "__eq", equality },
    { "__add", addition },
    { "__sub", subtraction },
    { "__mul", multiplication },
    { "__div", division },
    { "__tostring", toString },
    { "__concat", concat },
    { NULL, NULL }
};
int LuaC::Vector2fLib::newVector2f(lua_State *l){
    //Stack: table (Vector2f), vals for x & y if desired
    bool initVals = (lua_gettop(l) == 3);
    Vector2f *v = Allocate(l);
    if (initVals)
        v->Set(luaL_checknumber(l, 2), luaL_checknumber(l, 3));

    return 1;
}
int LuaC::Vector2fLib::getX(lua_State *l){
    //Stack: userdata (Vector2f)
    Vector2f *v = Check(l, 1);
    lua_pushnumber(l, v->x);
    return 1;
}
int LuaC::Vector2fLib::getY(lua_State *l){
    //Stack: userdata (Vector2f)
    Vector2f *v = Check(l, 1);
    lua_pushnumber(l, v->y);
    return 1;
}
int LuaC::Vector2fLib::newIndex(lua_State *l){
    //Stack: userdata (Vector2f), string of index to set, val for index
    std::string index = luaL_checkstring(l, 2);
    //Note that "set" is a function, not a value for __newindex
    switch (index.at(0)){
        case 'x':
            return setX(l);
        case 'y':
            return setY(l);
        default:
            break;
    }
    return 0;
}
int LuaC::Vector2fLib::set(lua_State *l){
    //Stack: userdata (Vector2f), val for x, val for y
    Vector2f *v = Check(l, 1);
    v->Set(luaL_checknumber(l, 2), luaL_checknumber(l, 3));
    return 0;
}
int LuaC::Vector2fLib::setX(lua_State *l){
    //Stack: userdata (Vector2f), val for x
    Vector2f *v = Check(l, 1);
    v->x = luaL_checknumber(l, 3);
    return 0;
}
int LuaC::Vector2fLib::setY(lua_State *l){
    //Stack: userdata (Vector2f), val for x, val for y
    Vector2f *v = Check(l, 1);
    v->y = luaL_checknumber(l, 3);
    return 0;
}
int LuaC::Vector2fLib::equality(lua_State *l){
    //Stack: userdata (Vector2f), userdata (Vector2f)
    Vector2f *v1 = Check(l, 1);
    Vector2f *v2 = Check(l, 2);
    lua_pushboolean(l, *v1 == *v2);
    return 1;
}
int LuaC::Vector2fLib::addition(lua_State *l){
    //Stack: userdata (Vector2f), userdata (Vector2f)
    Vector2f *v1 = Check(l, 1);
    Vector2f *v2 = Check(l, 2);
    //Calculate and push the result
    Vector2f res = *v1 + *v2;
    Push(&res, l);
    return 1;
}
int LuaC::Vector2fLib::subtraction(lua_State *l){
    //Stack: userdata (Vector2f), userdata (Vector2f)
    Vector2f *v1 = Check(l, 1);
    Vector2f *v2 = Check(l, 2);
    //Calculate and push the result
    Vector2f res = *v1 - *v2;
    Push(&res, l);
    return 1;
}
int LuaC::Vector2fLib::multiplication(lua_State *l){
    /*
    * There are 3 possible stacks we may get
    * 1. number, udata (Vector2f)
    * 2. udata (Vector2f), number
    * 3. udata (Vector2f), udata (Vector2f)
    */
    //Case 1:
    if (lua_type(l, 1) == LUA_TNUMBER)
        multWithFloat(l, 2, 1);
    //Case 2:
    else if (lua_type(l, 2) == LUA_TNUMBER)
        multWithFloat(l, 1, 2);
    //Case 3:
    else {
        Vector2f *v1 = Check(l, 1);
        Vector2f *v2 = Check(l, 2);
        //Calculate and push the result
        Vector2f res = (*v1) * (*v2);
        Push(&res, l);
    }
    return 1;
}
void LuaC::Vector2fLib::multWithFloat(lua_State *l, int vIdx, int fIdx){
    //Stack: userdata (Vector2f) and float at indices vIdx and fIdx respectively
    Vector2f *v = Check(l, vIdx);
    float num = luaL_checknumber(l, fIdx);
    //Calculate and push the result
    Vector2f res = (*v) * num;
    Push(&res, l);
}
int LuaC::Vector2fLib::division(lua_State *l){
    /*
    * There are 2 possible stacks we may get
    * 1. udata (Vector2f), number
    * 3. udata (Vector2f), udata (Vector2f)
    */
    //Case 1:
    if (lua_type(l, 2) == LUA_TNUMBER){
        Vector2f *v = Check(l, 1);
        float num = luaL_checknumber(l, 2);
        //Calculate and push the result
        Vector2f res = (*v) / num;
        Push(&res, l);
    }
    //Case 2:
    else {
        Vector2f *v1 = Check(l, 1);
        Vector2f *v2 = Check(l, 2);
        //Calculate and push the result
        Vector2f res = (*v1) / (*v2);
        Push(&res, l);
    }
    return 1;
}
int LuaC::Vector2fLib::toString(lua_State *l){
    //Stack: userdata (Vector2f)
    Vector2f *v = Check(l, 1);
    lua_pushstring(l, ((std::string)(*v)).c_str());
    return 1;
}
int LuaC::Vector2fLib::concat(lua_State *l){
    /*
    *  Stack has 2 possible configurations
    *  1. string, userdata (Vector2f)
    *  2. userdata (Vector2f), string
    */
    if (lua_type(l, 1) == LUA_TSTRING)
        concatWithString(l, 2, 1);
    else
        concatWithString(l, 1, 2);

    return 1;
}
void LuaC::Vector2fLib::concatWithString(lua_State *l, int vIdx, int sIdx){
    //Stack: userdata (Vector2f) @ vIdx, string @ sIdx
    Vector2f *v = Check(l, vIdx);
    std::string s = luaL_checkstring(l, sIdx);
    //Add the strings with the proper ordering
    if (vIdx < sIdx)
        lua_pushstring(l, ((std::string)(*v) + s).c_str());
    else
        lua_pushstring(l, (s + (std::string)(*v)).c_str());
}
