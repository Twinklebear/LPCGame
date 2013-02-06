#include <string>
#include <lua.hpp>
#include "core/math.h"
#include "core/debug.h"
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
int LuaC::MathLib::distance(lua_State *l){
    //Stack: Vector2f vA, Vector2f vB. Where we want the distance between these vectors
    Vector2f *vA = Vector2fLib::Check(l, 1);
    Vector2f *vB = Vector2fLib::Check(l, 2);
    lua_pushnumber(l, Math::Distance(*vA, *vB));
    return 1;
}
int LuaC::MathLib::clamp(lua_State *l){
    //Stack: number to clamp, min val, max val
    float x = luaL_checknumber(l, 1);
    float min = luaL_checknumber(l, 2);
    float max = luaL_checknumber(l, 3);
    lua_pushnumber(l, Math::Clamp(x, min, max));
    return 1;
}
int LuaC::MathLib::magnitude(lua_State *l){
    //Stack: Vector2f
    Vector2f *v = Vector2fLib::Check(l, 1);
    lua_pushnumber(l, Math::Magnitude(*v));
    return 1;
}
int LuaC::MathLib::normalize(lua_State *l){
    //Stack: Vector2f
    Vector2f *v = Vector2fLib::Check(l, 1);
    Vector2f unit = Math::Normalize(*v);
    Vector2fLib::Push(l, &unit);
    return 1;
}
int LuaC::MathLib::lerp(lua_State *l){
    //Stack: Vector2f start, Vector2f end, float percent
    Vector2f *start = Vector2fLib::Check(l, 1);
    Vector2f *end = Vector2fLib::Check(l, 2);
    float percent = luaL_checknumber(l, 3);
    Vector2f lerped = Math::Lerp(*start, *end, percent);
    Vector2fLib::Push(l, &lerped);
    return 1;
}
int LuaC::MathLib::forwardVector(lua_State *l){
    //Stack: float 
    float degrees = luaL_checknumber(l, 1);
    Vector2f v = Math::ForwardVector(degrees);
    Vector2fLib::Push(l, &v);
    return 1;
}
int LuaC::MathLib::rectNearRect(lua_State *l){
    //Stack: Rectf rA, Rectf rB, tolerance distance
    //We want to know if the Rect's are within tolerance dist of each other, and
    //if so which side of A is closest to B
    Rectf *rA = RectfLib::Check(l, 1);
    Rectf *rB = RectfLib::Check(l, 2);
    int tolerance = luaL_checkint(l, 3);
    int side = Math::RectNearRect(*rA, *rB, tolerance);
    lua_pushinteger(l, side);
    return 1;
}
int LuaC::MathLib::checkCollision(lua_State *l){
    /*
    *  Two possible stacks:
    *  1. Rectf, Rectf
    *  2. Vector2f, Rectf
    *  and we want to know if the objects are colliding/intersecting
    */
    if (LuaScriptLib::readType(l, 1) == rectfClass){
        Rectf *rA = RectfLib::Check(l, 1);
        Rectf *rB = RectfLib::Check(l, 2);
        bool coll = Math::CheckCollision(*rA, *rB);
        lua_pushboolean(l, coll);
    }
    else if (LuaScriptLib::readType(l, 1) == vector2fClass){
        Vector2f *v = Vector2fLib::Check(l, 1);
        Rectf *r = RectfLib::Check(l, 2);
        bool coll = Math::CheckCollision(*v, *r);
        lua_pushboolean(l, coll);
    }
    else {
        Debug::Log("Math.checkCollision Error: first type must be a Rectf or Vector2f");
        lua_pushnil(l);
    }
    return 1;
}
int LuaC::MathLib::toSceneSpace(lua_State *l){
    /*
    *  Two possible stacks:
    *  1. Camera, Rectf
    *  2. Camera, Vector2f
    *  and we want to transform the position into scene space
    */
    std::weak_ptr<Camera> *cam = CameraLib::Check(l, 1);
    if (LuaScriptLib::readType(l, 2) == rectfClass){
        Rectf *r = RectfLib::Check(l, 2);
        Rectf transform = Math::ToSceneSpace(*cam, *r);
        RectfLib::Push(l, &transform);
    }
    else if (LuaScriptLib::readType(l, 2) == vector2fClass){
        Vector2f *v = Vector2fLib::Check(l, 2);
        Vector2f transform = Math::ToSceneSpace(*cam, *v);
        Vector2fLib::Push(l, &transform);
    }
    else {
        Debug::Log("Math.toSceneSpace Error: Must have a Rectf or Vector2f to transform");
        lua_pushnil(l);
    }
    return 1;
}
int LuaC::MathLib::fromSceneSpace(lua_State *l){
    /*
    *  Two possible stacks:
    *  1. Camera, Rectf
    *  2. Camera, Vector2f
    *  and we want to transform the position into scene space
    */
    std::weak_ptr<Camera> *cam = CameraLib::Check(l, 1);
    if (LuaScriptLib::readType(l, 2) == rectfClass){
        Rectf *r = RectfLib::Check(l, 2);
        Rectf transform = Math::FromSceneSpace(*cam, *r);
        RectfLib::Push(l, &transform);
    }
    else if (LuaScriptLib::readType(l, 2) == vector2fClass){
        Vector2f *v = Vector2fLib::Check(l, 2);
        Vector2f transform = Math::FromSceneSpace(*cam, *v);
        Vector2fLib::Push(l, &transform);
    }
    else {
        Debug::Log("Math.fromSceneSpace Error: Must have a Rectf or Vector2f to transform");
        lua_pushnil(l);
    }
    return 1;
}