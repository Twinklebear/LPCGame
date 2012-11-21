#include <string>
#include <lua.hpp>
#include "src/debug.h"
#include "src/physics.h"
#include "luacscript.h"
#include "luacvector2f.h"
#include "luacrectf.h"
#include "luacphysics.h"

int LuaC::PhysicsLib::luaopen_physics(lua_State *l){
    //We use a custom registration because Physics class shouldn't have a constructor
    //exposed to Lua
    //Stack: lib name
    //Push the metatable to contain the fcns onto the stack
    luaL_newmetatable(l, physicsMeta.c_str());
    //Copy metatable from -1 to the top
    lua_pushvalue(l, -1);
    //Set table at -2 key of __index = top of stack
    //ie. LPC.Physics.__index = table at top, ie. itself
    lua_setfield(l, -2, "__index");
    //Register the lib to the metatable at top of stack
    luaL_register(l, NULL, luaPhysicsLib);
    //Stack: lib name, metatable
    //Add type identifier to the metatable
    lua_pushstring(l, physicsClass.c_str());
    lua_setfield(l, -2, "type");
    //Stack: lib name, metatable
    return 1;
}
void LuaC::PhysicsLib::addPhysics(lua_State *l, int i){
    LuaScriptLib::Add(l, i, physicsMeta);
}
std::weak_ptr<Physics>* LuaC::PhysicsLib::checkPhysics(lua_State *l, int i){
    return (std::weak_ptr<Physics>*)luaL_checkudata(l, i, physicsMeta.c_str());
}
void LuaC::PhysicsLib::PushPhysics(std::weak_ptr<Physics> *physics, lua_State *l){
    std::weak_ptr<Physics> *p = AllocatePhysics(l);
    *p = *physics;
}
void LuaC::PhysicsLib::CopyPhysics(lua_State *from, int idx, lua_State *too){
    std::weak_ptr<Physics> *p = checkPhysics(from, idx);
    PushPhysics(p, too);
}
std::weak_ptr<Physics>* LuaC::PhysicsLib::AllocatePhysics(lua_State *l){
    void *block = lua_newuserdata(l, sizeof(std::weak_ptr<Physics>));
    std::weak_ptr<Physics> *p = new(block) std::weak_ptr<Physics>();
    addPhysics(l, -1);
    return p;
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
    std::weak_ptr<Physics> *pWeak = checkPhysics(l, 1);
    if (pWeak->expired()){
        std::string err = "PhysicsLib:position error: Failed to lock Physics weak ptr";
        Debug::Log(err);
        lua_pushstring(l, err.c_str());
        return 1;
    }
    std::shared_ptr<Physics> p = pWeak->lock();
    //Make a new vector and set it
    Vector2f *v = Vector2fLib::AllocateVector2f(l);
    *v = p->Position();
    return 1;
}
int LuaC::PhysicsLib::velocity(lua_State *l){
    //Stack: userdata (Physics)
    std::weak_ptr<Physics> *pWeak = checkPhysics(l, 1);
    if (pWeak->expired()){
        std::string err = "PhysicsLib:velocity error: Failed to lock Physics weak ptr";
        Debug::Log(err);
        lua_pushstring(l, err.c_str());
        return 1;
    }
    std::shared_ptr<Physics> p = pWeak->lock();
    //Make a new vector and set it
    Vector2f *v = Vector2fLib::AllocateVector2f(l);
    *v = p->Velocity();
    return 1;
}
int LuaC::PhysicsLib::acceleration(lua_State *l){
    //Stack: userdata (Physics)
    std::weak_ptr<Physics> *pWeak = checkPhysics(l, 1);
    if (pWeak->expired()){
        std::string err = "PhysicsLib:acceleration error: Failed to lock Physics weak ptr";
        Debug::Log(err);
        lua_pushstring(l, err.c_str());
        return 1;
    }
    std::shared_ptr<Physics> p = pWeak->lock();
    //Make a new vector and set it
    Vector2f *v = Vector2fLib::AllocateVector2f(l);
    *v = p->Acceleration();
    return 1;
}
int LuaC::PhysicsLib::box(lua_State *l){
    //Stack: userdata (Physics)
    std::weak_ptr<Physics> *pWeak = checkPhysics(l, 1);
    if (pWeak->expired()){
        std::string err = "PhysicsLib:box error: Failed to lock Physics weak ptr";
        Debug::Log(err);
        lua_pushstring(l, err.c_str());
        return 1;
    }
    std::shared_ptr<Physics> p = pWeak->lock();
    //Make a new rectf and set it
    Rectf *r = RectfLib::AllocateRectf(l);
    *r = p->Box();
    return 1;
}
int LuaC::PhysicsLib::state(lua_State *l){
    //Stack: userdata (Physics)
    std::weak_ptr<Physics> *pWeak = checkPhysics(l, 1);
    if (pWeak->expired()){
        std::string err = "PhysicsLib:box error: Failed to lock Physics weak ptr";
        Debug::Log(err);
        lua_pushstring(l, err.c_str());
        return 1;
    }
    std::shared_ptr<Physics> p = pWeak->lock();
    //Get the state end push it
    lua_pushnumber(l, p->State());
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
    std::weak_ptr<Physics> *pWeak = checkPhysics(l, 1);
    if (pWeak->expired()){
        std::string err = "PhysicsLib:setPosition error: Failed to lock Physics weak ptr";
        Debug::Log(err);
        lua_pushstring(l, err.c_str());
        return 1;
    }
    std::shared_ptr<Physics> p = pWeak->lock();
    Vector2f *v = Vector2fLib::checkVector2f(l, 2);
    p->SetPosition(*v);
    return 0;
}
int LuaC::PhysicsLib::setVelocity(lua_State *l){
    //Stack: userdata (Physics), userdata (Vector2f)
    std::weak_ptr<Physics> *pWeak = checkPhysics(l, 1);
    if (pWeak->expired()){
        std::string err = "PhysicsLib:setVelocity error: Failed to lock Physics weak ptr";
        Debug::Log(err);
        lua_pushstring(l, err.c_str());
        return 1;
    }
    std::shared_ptr<Physics> p = pWeak->lock();
    Vector2f *v = Vector2fLib::checkVector2f(l, 2);
    p->SetVelocity(*v);
    return 0;
}
int LuaC::PhysicsLib::setAcceleration(lua_State *l){
    //Stack: userdata (Physics), userdata (Vector2f)
    std::weak_ptr<Physics> *pWeak = checkPhysics(l, 1);
    if (pWeak->expired()){
        std::string err = "PhysicsLib:setAcceleration error: Failed to lock Physics weak ptr";
        Debug::Log(err);
        lua_pushstring(l, err.c_str());
        return 1;
    }
    std::shared_ptr<Physics> p = pWeak->lock();
    Vector2f *v = Vector2fLib::checkVector2f(l, 2);
    p->SetAcceleration(*v);
    return 0;
}
int LuaC::PhysicsLib::setHorizDir(lua_State *l){
    //Stack: userdata (Physics), int for horiz dir
    std::weak_ptr<Physics> *pWeak = checkPhysics(l, 1);
    if (pWeak->expired()){
        std::string err = "PhysicsLib:setHorizDir error: Failed to lock Physics weak ptr";
        Debug::Log(err);
        lua_pushstring(l, err.c_str());
        return 1;
    }
    std::shared_ptr<Physics> p = pWeak->lock();
    int dir = luaL_checkint(l, 2);
    p->SetHorizDir(dir);
    return 0;
}
int LuaC::PhysicsLib::setVertDir(lua_State *l){
    //Stack: userdata (Physics), int for vert dir
    std::weak_ptr<Physics> *pWeak = checkPhysics(l, 1);
    if (pWeak->expired()){
        std::string err = "PhysicsLib:setVertDir error: Failed to lock Physics weak ptr";
        Debug::Log(err);
        lua_pushstring(l, err.c_str());
        return 1;
    }
    std::shared_ptr<Physics> p = pWeak->lock();
    int dir = luaL_checkint(l, 2);
    p->SetVertDir(dir);
    return 0;
}
int LuaC::PhysicsLib::setBox(lua_State *l){
    //Stack: userdata (Physics), userdata (Rectf)
    std::weak_ptr<Physics> *pWeak = checkPhysics(l, 1);
    if (pWeak->expired()){
        std::string err = "PhysicsLib:setBox error: Failed to lock Physics weak ptr";
        Debug::Log(err);
        lua_pushstring(l, err.c_str());
        return 1;
    }
    std::shared_ptr<Physics> p = pWeak->lock();
    Rectf *r = RectfLib::checkRectf(l, 2);
    p->SetBox(*r);
    return 0;
}
int LuaC::PhysicsLib::toString(lua_State *l){
    return 1;
}
int LuaC::PhysicsLib::concat(lua_State *l){
    return 1;
}