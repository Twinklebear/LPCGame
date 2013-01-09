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
    std::weak_ptr<Physics> *pWeak = Check(l, 1);
    if (pWeak->expired()){
        std::string err = "PhysicsLib:position error: Failed to lock Physics weak ptr";
        Debug::Log(err);
        lua_pushstring(l, err.c_str());
        return 1;
    }
    std::shared_ptr<Physics> p = pWeak->lock();
    Vector2fLib::Push(&p->Position(), l);
    return 1;
}
int LuaC::PhysicsLib::velocity(lua_State *l){
    //Stack: userdata (Physics)
    std::weak_ptr<Physics> *pWeak = Check(l, 1);
    if (pWeak->expired()){
        std::string err = "PhysicsLib:velocity error: Failed to lock Physics weak ptr";
        Debug::Log(err);
        lua_pushstring(l, err.c_str());
        return 1;
    }
    std::shared_ptr<Physics> p = pWeak->lock();
    Vector2fLib::Push(&p->Velocity(), l);
    return 1;
}
int LuaC::PhysicsLib::acceleration(lua_State *l){
    //Stack: userdata (Physics)
    std::weak_ptr<Physics> *pWeak = Check(l, 1);
    if (pWeak->expired()){
        std::string err = "PhysicsLib:acceleration error: Failed to lock Physics weak ptr";
        Debug::Log(err);
        lua_pushstring(l, err.c_str());
        return 1;
    }
    std::shared_ptr<Physics> p = pWeak->lock();
    Vector2fLib::Push(&p->Acceleration(), l);
    return 1;
}
int LuaC::PhysicsLib::box(lua_State *l){
    //Stack: userdata (Physics)
    std::weak_ptr<Physics> *pWeak = Check(l, 1);
    if (pWeak->expired()){
        std::string err = "PhysicsLib:box error: Failed to lock Physics weak ptr";
        Debug::Log(err);
        lua_pushstring(l, err.c_str());
        return 1;
    }
    std::shared_ptr<Physics> p = pWeak->lock();
    RectfLib::Push(&p->Box(), l);
    return 1;
}
int LuaC::PhysicsLib::state(lua_State *l){
    //Stack: userdata (Physics)
    std::weak_ptr<Physics> *pWeak = Check(l, 1);
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
    std::weak_ptr<Physics> *pWeak = Check(l, 1);
    if (pWeak->expired()){
        std::string err = "PhysicsLib:setPosition error: Failed to lock Physics weak ptr";
        Debug::Log(err);
        lua_pushstring(l, err.c_str());
        return 1;
    }
    std::shared_ptr<Physics> p = pWeak->lock();
    Vector2f *v = Vector2fLib::Check(l, 2);
    p->SetPosition(*v);
    return 0;
}
int LuaC::PhysicsLib::setVelocity(lua_State *l){
    //Stack: userdata (Physics), userdata (Vector2f)
    std::weak_ptr<Physics> *pWeak = Check(l, 1);
    if (pWeak->expired()){
        std::string err = "PhysicsLib:setVelocity error: Failed to lock Physics weak ptr";
        Debug::Log(err);
        lua_pushstring(l, err.c_str());
        return 1;
    }
    std::shared_ptr<Physics> p = pWeak->lock();
    Vector2f *v = Vector2fLib::Check(l, 2);
    p->SetVelocity(*v);
    return 0;
}
int LuaC::PhysicsLib::setAcceleration(lua_State *l){
    //Stack: userdata (Physics), userdata (Vector2f)
    std::weak_ptr<Physics> *pWeak = Check(l, 1);
    if (pWeak->expired()){
        std::string err = "PhysicsLib:setAcceleration error: Failed to lock Physics weak ptr";
        Debug::Log(err);
        lua_pushstring(l, err.c_str());
        return 1;
    }
    std::shared_ptr<Physics> p = pWeak->lock();
    Vector2f *v = Vector2fLib::Check(l, 2);
    p->SetAcceleration(*v);
    return 0;
}
int LuaC::PhysicsLib::setHorizDir(lua_State *l){
    //Stack: userdata (Physics), int for horiz dir
    std::weak_ptr<Physics> *pWeak = Check(l, 1);
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
    std::weak_ptr<Physics> *pWeak = Check(l, 1);
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
    std::weak_ptr<Physics> *pWeak = Check(l, 1);
    if (pWeak->expired()){
        std::string err = "PhysicsLib:setBox error: Failed to lock Physics weak ptr";
        Debug::Log(err);
        lua_pushstring(l, err.c_str());
        return 1;
    }
    std::shared_ptr<Physics> p = pWeak->lock();
    Rectf *r = RectfLib::Check(l, 2);
    p->SetBox(*r);
    return 0;
}
int LuaC::PhysicsLib::toString(lua_State *l){
    return 1;
}
int LuaC::PhysicsLib::concat(lua_State *l){
    return 1;
}