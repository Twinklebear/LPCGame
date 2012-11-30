#include <string>
#include <lua.hpp>
#include "src/math.h"
#include "src/debug.h"
#include "luacvector2f.h"
#include "luacrectf.h"
#include "luaccamera.h"
#include "luacscript.h"
#include "luacmath.h"

int LuaC::MathLib::luaopen_math(lua_State *l){
    //Stack: lib name
    //Register the library as global table "Math"
    luaL_register(l, mathClass.c_str(), luaMathLib);
    //Stack: lib name, table
    openDirEnum(l);
    return 0;
}
const struct luaL_reg LuaC::MathLib::luaMathLib[] = {
    { "distance", distance },
    { "clamp", clamp },
    { "magnitude", magnitude },
    { "normalize", normalize },
    { "lerp", lerp },
    { "forwardVector", forwardVector },
    { "rectNearRect", rectNearRect },
    { "checkCollision", checkCollision },
    { "toSceneSpace", toSceneSpace },
    { "fromSceneSpace", fromSceneSpace },
    { NULL, NULL }
};
void LuaC::MathLib::openDirEnum(lua_State *l){
    //Stack: lib name, table
    lua_pushinteger(l, Math::UP);
    lua_setfield(l, -2, "UP");
    lua_pushinteger(l, Math::DOWN);
    lua_setfield(l, -2, "DOWN");
    lua_pushinteger(l, Math::LEFT);
    lua_setfield(l, -2, "LEFT");
    lua_pushinteger(l, Math::RIGHT);
    lua_setfield(l, -2, "RIGHT");
}
int LuaC::MathLib::distance(lua_State *l){
    //Stack: vectorA, vectorB. We want the distance between these vectors
    if (LuaScriptLib::readType(l, 1) == vector2fClass && LuaScriptLib::readType(l, 2) == vector2fClass){
        Vector2f *vA = Vector2fLib::checkVector2f(l, 1);
        Vector2f *vB = Vector2fLib::checkVector2f(l, 2);
        lua_pushnumber(l, Math::Distance(*vA, *vB));
    }
    else {
        Debug::Log("Math.distance error: Params must be two Vector2f");
        lua_pushnil(l);
    }

    return 1;
}
int LuaC::MathLib::clamp(lua_State *l){
    return 1;
}
int LuaC::MathLib::magnitude(lua_State *l){
    return 1;
}
int LuaC::MathLib::normalize(lua_State *l){
    return 1;
}
int LuaC::MathLib::lerp(lua_State *l){
    return 1;
}
int LuaC::MathLib::forwardVector(lua_State *l){
    return 1;
}
int LuaC::MathLib::rectNearRect(lua_State *l){
    return 1;
}
int LuaC::MathLib::checkCollision(lua_State *l){
    return 1;
}
int LuaC::MathLib::toSceneSpace(lua_State *l){
    return 1;
}
int LuaC::MathLib::fromSceneSpace(lua_State *l){
    return 1;
}