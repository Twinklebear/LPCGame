#include <string>
#include <lua.hpp>     
#include "src/vectors.h"
#include "luacscript.h"
#include "luacvector2f.h"

const std::string LuaC::Vector2fLib::sMetatable = "LPC.Vector2f";
const std::string LuaC::Vector2fLib::sClassName = "Vector2f";

int LuaC::Vector2fLib::luaopen_vector2f(lua_State *l){
    return LuaScriptLib::LuaOpenLib(l, sMetatable, sClassName, luaVector2fLib, newVector2f);
}
void LuaC::Vector2fLib::addVector2f(lua_State *l, int i){
    LuaScriptLib::Add(l, i, sMetatable);
}
Vector2f* LuaC::Vector2fLib::checkVector2f(lua_State *l, int i){
    return (Vector2f*)luaL_checkudata(l, i, sMetatable.c_str());
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
    Vector2f *v = (Vector2f*)lua_newuserdata(l, sizeof(Vector2f));
    if (initVals)
        v->Set(luaL_checknumber(l, 2), luaL_checknumber(l, 3));
    else
        v->Set(0, 0);
    addVector2f(l, -1);
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
    std::string val = luaL_checkstring(l, 2);
    lua_remove(l, 2);
    //Stack: userdata (Vector2f), val to set
    //Note that "set" is a function, not a value for __newindex
    switch (val.at(0)){
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
        multVectorWithFloat(l, 2, 1);
    //Case 2:
    else if (lua_type(l, 2) == LUA_TNUMBER)
        multVectorWithFloat(l, 1, 2);
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
void LuaC::Vector2fLib::multVectorWithFloat(lua_State *l, int vIdx, int fIdx){
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
    //Need to write std::string conversion for vector2f
    return 1;
}
int LuaC::Vector2fLib::concat(lua_State *l){
    //See toString note
    return 1;
}