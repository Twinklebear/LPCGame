#include <string>
#include <lua.hpp>
#include "luaref.h"

LuaC::LuaRef::LuaRef(lua_State *l, int i) : mRef(LUA_REFNIL), mState(l) {
    lua_pushvalue(mState, i);
    mRef = luaL_ref(mState, LUA_REGISTRYINDEX);
}
LuaC::LuaRef::LuaRef(lua_State *l, std::string name) : mRef(LUA_REFNIL), mState(l) {
    lua_getglobal(mState, name.c_str());
    mRef = luaL_ref(mState, LUA_REGISTRYINDEX);
}
LuaC::LuaRef::~LuaRef(){
    luaL_unref(mState, LUA_REGISTRYINDEX, mRef);
}
void LuaC::LuaRef::Push(lua_State *l) const {
    //Make sure the state we want to push into is the one the reference exists in
    _ASSERT(mState == l);
    lua_rawgeti(mState, LUA_REGISTRYINDEX, mRef);
}
void LuaC::LuaRef::Push(lua_State *l, std::string name) const {
    //Make sure the state we want to push into is the one the reference exists in
    _ASSERT(mState == l);
    lua_rawgeti(mState, LUA_REGISTRYINDEX, mRef);
    lua_setglobal(l, name.c_str());
}
