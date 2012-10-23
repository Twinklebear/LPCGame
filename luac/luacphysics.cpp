#include <string>
#include <lua.hpp>
#include "src/physics.h"
#include "luacscript.h"
#include "luacvector2f.h"
#include "luacrectf.h"
#include "luacphysics.h"

const std::string LuaC::PhysicsLib::sMetatable = "LPC.Physics";
const std::string LuaC::PhysicsLib::sClassName = "Physics";

int LuaC::PhysicsLib::luaopen_physics(lua_State *l){
    //Stack: lib name
    //Push the metatable to contain the fcns onto the stack
    luaL_newmetatable(l, sMetatable.c_str());
    //Copy metatable from -1 to the top
    lua_pushvalue(l, -1);
    //Set table at -2 key of __index = top of stack
    //ie. LPC.LuaRect.__index = table containing luaRectLib_m
    lua_setfield(l, -2, "__index");
    //Register the lib to the metatable at top of stack
    luaL_register(l, NULL, luaPhysicsLib);
    //Stack: lib name, metatable
    //Add type identifier to the metatable
    lua_pushstring(l, sClassName.c_str());
    lua_setfield(l, -2, "type");
    //Stack: lib name, metatable
    return 1;
}
void LuaC::PhysicsLib::addPhysics(lua_State *l, int i){
    LuaScriptLib::Add(l, i, sMetatable);
}
Physics** LuaC::PhysicsLib::checkPhysics(lua_State *l, int i){
    return (Physics**)luaL_checkudata(l, i, sMetatable.c_str());
}
const struct luaL_reg LuaC::PhysicsLib::luaPhysicsLib[] = {
    { "position", position },
    { "velocity", velocity },
    { "acceleration", acceleration },
    { "box", box },
    { "state", state },
    { "__newindex", accessor },
    { "__tostring", toString },
    { "__concat", concat },
    { NULL, NULL }
};
int LuaC::PhysicsLib::position(lua_State *l){
    //Stack: userdata (Physics)
    Physics **p = checkPhysics(l, 1);
    //Make a new vector and set it
    Vector2f *v = (Vector2f*)lua_newuserdata(l, sizeof(Vector2f));
    Vector2fLib::addVector2f(l, -1);
    v->Set((*p)->Position());
    return 1;
}
int LuaC::PhysicsLib::velocity(lua_State *l){
    //Stack: userdata (Physics)
    Physics **p = checkPhysics(l, 1);
    //Make a new vector and set it
    Vector2f *v = (Vector2f*)lua_newuserdata(l, sizeof(Vector2f));
    Vector2fLib::addVector2f(l, -1);
    v->Set((*p)->Velocity());
    return 1;
}
int LuaC::PhysicsLib::acceleration(lua_State *l){
    //Stack: userdata (Physics)
    Physics **p = checkPhysics(l, 1);
    //Make a new vector and set it
    Vector2f *v = (Vector2f*)lua_newuserdata(l, sizeof(Vector2f));
    Vector2fLib::addVector2f(l, -1);
    v->Set((*p)->Acceleration());
    return 1;
}
int LuaC::PhysicsLib::box(lua_State *l){
    //Stack: userdata (Physics)
    Physics **p = checkPhysics(l, 1);
    //Make a new rectf and set it
    Rectf *r = (Rectf*)lua_newuserdata(l, sizeof(Rectf));
    RectfLib::addRectf(l, -1);
    r->Set((*p)->Box());
    return 1;
}
int LuaC::PhysicsLib::state(lua_State *l){
    //Stack: userdata (Physics)
    Physics **p = checkPhysics(l, 1);
    //Get the state end push it
    lua_pushnumber(l, (*p)->State());
    return 1;
}
int LuaC::PhysicsLib::accessor(lua_State *l){
    //Stack: userdata (Physics), index to set, val to set for index
    std::string index = luaL_checkstring(l, 2);
    lua_remove(l, 2);
    switch (index.at(0)){
        case 'p':
            return setPosition(l);
        case 'v':
            //We must check the third char, for l or r to tell which we want
            //velocity or vertDir
            return ((index.at(2) == 'l') ? setVelocity(l) : setVertDir(l));
        case 'a':
            return setAcceleration(l);
        case 'b':
            return setBox(l);
        default:
            break;
    }
    return 0;
}
int LuaC::PhysicsLib::setPosition(lua_State *l){
    //Stack: userdata (Physics), userdata (Vector2f)
    Physics **p = checkPhysics(l, 1);
    Vector2f *v = Vector2fLib::checkVector2f(l, 2);
    (*p)->SetPosition(*v);
    return 0;
}
int LuaC::PhysicsLib::setVelocity(lua_State *l){
    //Stack: userdata (Physics), userdata (Vector2f)
    Physics **p = checkPhysics(l, 1);
    Vector2f *v = Vector2fLib::checkVector2f(l, 2);
    (*p)->SetVelocity(*v);
    return 0;
}
int LuaC::PhysicsLib::setAcceleration(lua_State *l){
    //Stack: userdata (Physics), userdata (Vector2f)
    Physics **p = checkPhysics(l, 1);
    Vector2f *v = Vector2fLib::checkVector2f(l, 2);
    (*p)->SetAcceleration(*v);
    return 0;
}
int LuaC::PhysicsLib::setHorizDir(lua_State *l){
    //Stack: userdata (Physics), int for horiz dir
    Physics **p = checkPhysics(l, 1);
    int dir = luaL_checkint(l, 2);
    (*p)->SetHorizDir(dir);
    return 0;
}
int LuaC::PhysicsLib::setVertDir(lua_State *l){
    //Stack: userdata (Physics), int for vert dir
    Physics **p = checkPhysics(l, 1);
    int dir = luaL_checkint(l, 2);
    (*p)->SetVertDir(dir);
    return 0;
}
int LuaC::PhysicsLib::setBox(lua_State *l){
    //Stack: userdata (Physics), userdata (Rectf)
    Physics **p = checkPhysics(l, 1);
    Rectf *r = RectfLib::checkRectf(l, 2);
    (*p)->SetBox(*r);
    return 0;
}
int LuaC::PhysicsLib::toString(lua_State *l){
    return 1;
}
int LuaC::PhysicsLib::concat(lua_State *l){
    return 1;
}