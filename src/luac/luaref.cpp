#include <string>
#include <memory>
#include <lua.hpp>
#include "luaref.h"

LuaC::LuaRef::LuaRef() 
    : mRef(std::make_shared<int>(LUA_REFNIL)), mL(NULL)
{
}
LuaC::LuaRef::LuaRef(lua_State *l, int i) 
    : mRef(std::make_shared<int>(LUA_REFNIL)), mL(l) 
{
    lua_pushvalue(mL, i);
    mRef = std::make_shared<int>(luaL_ref(mL, LUA_REGISTRYINDEX));
}
LuaC::LuaRef::LuaRef(lua_State *l, std::string name) 
    : mRef(std::make_shared<int>(LUA_REFNIL)), mL(l) 
{
    lua_getglobal(mL, name.c_str());
    mRef = std::make_shared<int>(luaL_ref(mL, LUA_REGISTRYINDEX));
}
LuaC::LuaRef::~LuaRef(){
    //If we're the last one using the reference, release it
    if (mRef.use_count() == 1 && mL != NULL)
        luaL_unref(mL, LUA_REGISTRYINDEX, *mRef);
}
void LuaC::LuaRef::Push(lua_State *l) const {
    //Make sure the state we want to push into is the one the reference exists in
    _ASSERT(mL == l);
    lua_rawgeti(mL, LUA_REGISTRYINDEX, *mRef);
}
void LuaC::LuaRef::Push(lua_State *l, std::string name) const {
    //Make sure the state we want to push into is the one the reference exists in
    _ASSERT(mL == l);
    lua_rawgeti(mL, LUA_REGISTRYINDEX, *mRef);
    lua_setglobal(l, name.c_str());
}
