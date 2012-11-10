#include <string>
#include <lua.hpp>
#include "src/vectors.h"
#include "luacscript.h"
#include "luacvector2f.h"

int LuaC::Vector2fLib::luaopen_vector2f(lua_State *l){
    return LuaScriptLib::LuaOpenLib(l, vector2fMeta, vector2fClass, luaVector2fLib, newVector2f);
}
void LuaC::Vector2fLib::addVector2f(lua_State *l, int i){
    LuaScriptLib::Add(l, i, vector2fMeta);
}
Vector2f* LuaC::Vector2fLib::checkVector2f(lua_State *l, int i){
    return (Vector2f*)luaL_checkudata(l, i, vector2fMeta.c_str());
}
void LuaC::Vector2fLib::PushVector2f(Vector2f *vector, lua_State *l){
    Vector2f *v = AllocateVector2f(l);
    v->Set(*vector);
}
void LuaC::Vector2fLib::CopyVector2f(lua_State *from, int idx, lua_State *too){
    //Get the Vector2f from the from state
    Vector2f *v = checkVector2f(from, idx);
    //Push a copy into the too state
    PushVector2f(v, too);
}
Vector2f* LuaC::Vector2fLib::AllocateVector2f(lua_State *l){
    Vector2f *v = (Vector2f*)lua_newuserdata(l, sizeof(Vector2f));
    addVector2f(l, -1);
    return v;
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
    Vector2f *v = AllocateVector2f(l);
    if (initVals)
        v->Set(luaL_checknumber(l, 2), luaL_checknumber(l, 3));
    else
        v->Set(0, 0);
    return 1;
}
int LuaC::Vector2fLib::getX(lua_State *l){
    //Stack: userdata (Vector2f)
    Vector2f *v = checkVector2f(l, 1);
    lua_pushnumber(l, v->x);
    return 1;
}
int LuaC::Vector2fLib::getY(lua_State *l){
    //Stack: userdata (Vector2f)
    Vector2f *v = checkVector2f(l, 1);
    lua_pushnumber(l, v->y);
    return 1;
}
int LuaC::Vector2fLib::newIndex(lua_State *l){
    //Stack: userdata (Vector2f), string of index to set, val for index
    std::string index = luaL_checkstring(l, 2);
    lua_remove(l, 2);
    //Stack: userdata (Vector2f), val to set
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
    Vector2f *v = checkVector2f(l, 1);
    v->Set(luaL_checknumber(l, 2), luaL_checknumber(l, 3));
    return 0;
}
int LuaC::Vector2fLib::setX(lua_State *l){
    //Stack: userdata (Vector2f), val for x
    Vector2f *v = checkVector2f(l, 1);
    v->Set(luaL_checknumber(l, 2), v->y);
    return 0;
}
int LuaC::Vector2fLib::setY(lua_State *l){
    //Stack: userdata (Vector2f), val for x, val for y
    Vector2f *v = checkVector2f(l, 1);
    v->Set(v->x, luaL_checknumber(l, 2));
    return 0;
}
int LuaC::Vector2fLib::equality(lua_State *l){
    //Stack: userdata (Vector2f), userdata (Vector2f)
    Vector2f *v1 = checkVector2f(l, 1);
    Vector2f *v2 = checkVector2f(l, 2);
    lua_pushboolean(l, *v1 == *v2);
    return 1;
}
int LuaC::Vector2fLib::addition(lua_State *l){
    //Stack: userdata (Vector2f), userdata (Vector2f)
    Vector2f *v1 = checkVector2f(l, 1);
    Vector2f *v2 = checkVector2f(l, 2);
    //Create the resultant vector
    Vector2f *res = (Vector2f*)lua_newuserdata(l, sizeof(Vector2f));
    addVector2f(l, -1);
    res->Set(*v1 + *v2);
    return 1;
}
int LuaC::Vector2fLib::subtraction(lua_State *l){
    //Stack: userdata (Vector2f), userdata (Vector2f)
    Vector2f *v1 = checkVector2f(l, 1);
    Vector2f *v2 = checkVector2f(l, 2);
    //Create the resultant vector
    Vector2f *res = (Vector2f*)lua_newuserdata(l, sizeof(Vector2f));
    addVector2f(l, -1);
    res->Set(*v1 - *v2);
    return 1;
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
        Vector2f *v1 = checkVector2f(l, 1);
        Vector2f *v2 = checkVector2f(l, 2);
        //Create the result
        Vector2f *res = (Vector2f*)lua_newuserdata(l, sizeof(Vector2f));
        res->Set((*v1) * (*v2));
    }
    //Add the metatable to the resultant vector
    addVector2f(l, -1);
    return 1;
}
void LuaC::Vector2fLib::multWithFloat(lua_State *l, int vIdx, int fIdx){
    //Stack: userdata (Vector2f) and float at indices vIdx and fIdx respectively
    Vector2f *v = checkVector2f(l, vIdx);
    float num = luaL_checknumber(l, fIdx);
    //Create the result
    Vector2f *res = (Vector2f*)lua_newuserdata(l, sizeof(Vector2f));
    res->Set((*v) * num);
}
int LuaC::Vector2fLib::division(lua_State *l){
    /*
    * There are 2 possible stacks we may get
    * 1. udata (Vector2f), number
    * 3. udata (Vector2f), udata (Vector2f)
    */
    //Case 1:
    if (lua_type(l, 2) == LUA_TNUMBER){
        Vector2f *v = checkVector2f(l, 1);
        float num = luaL_checknumber(l, 2);
        //Create the result
        Vector2f *res = (Vector2f*)lua_newuserdata(l, sizeof(Vector2f));
        res->Set((*v) / num);
    }
    //Case 2:
    else {
        Vector2f *v1 = checkVector2f(l, 1);
        Vector2f *v2 = checkVector2f(l, 2);
        //Create the result
        Vector2f *res = (Vector2f*)lua_newuserdata(l, sizeof(Vector2f));
        res->Set((*v1) / (*v2));
    }
    addVector2f(l, -1);
    return 1;
}
int LuaC::Vector2fLib::toString(lua_State *l){
    //Stack: userdata (Vector2f)
    Vector2f *v = checkVector2f(l, 1);
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
    Vector2f *v = checkVector2f(l, vIdx);
    std::string s = luaL_checkstring(l, sIdx);
    //Add the strings with the proper ordering
    if (vIdx < sIdx)
        lua_pushstring(l, ((std::string)(*v) + s).c_str());
    else
        lua_pushstring(l, (s + (std::string)(*v)).c_str());
}
