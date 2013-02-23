#include <string>
#include <memory>
#include <lua.hpp>
#include "luaref.h"

#include "core/debug.h"

LuaC::LuaRef::LuaRef() 
    : mRef(std::make_shared<int>(LUA_REFNIL)), mState(NULL)
{
}
LuaC::LuaRef::LuaRef(lua_State *l, int i) 
    : mRef(std::make_shared<int>(LUA_REFNIL)), mState(l) 
{
    //lua_pushvalue(mState, i);
    Debug::Log("Storing ref to data @ i: " + (char)i);
    LuaC::LuaScriptLib::StackDump(l);
    mRef = std::make_shared<int>(luaL_ref(mState, LUA_REGISTRYINDEX));
}
LuaC::LuaRef::LuaRef(lua_State *l, std::string name) 
    : mRef(std::make_shared<int>(LUA_REFNIL)), mState(l) 
{
    Debug::Log("Storing ref to global data: " + name);
    lua_getglobal(mState, name.c_str());
    LuaC::LuaScriptLib::StackDump(l);
    mRef = std::make_shared<int>(luaL_ref(mState, LUA_REGISTRYINDEX));
}
LuaC::LuaRef::~LuaRef(){
    //If we're the last one using the reference, release it
    if (mRef.use_count() == 1)
        luaL_unref(mState, LUA_REGISTRYINDEX, *mRef);
}
void LuaC::LuaRef::Push(lua_State *l) const {
    //Make sure the state we want to push into is the one the reference exists in
    _ASSERT(mState == l);
    lua_rawgeti(mState, LUA_REGISTRYINDEX, *mRef);
}
void LuaC::LuaRef::Push(lua_State *l, std::string name) const {
    //Make sure the state we want to push into is the one the reference exists in
    _ASSERT(mState == l);
    lua_rawgeti(mState, LUA_REGISTRYINDEX, *mRef);
    lua_setglobal(l, name.c_str());
}
