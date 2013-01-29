#include <string>
#include <lua.hpp>
#include "luaref.h"

LuaRef::LuaRef(lua_State *l, int i) : mRef(LUA_REFNIL), mState(l) {
    lua_pushvalue(mState, i);
    mRef = luaL_ref(mState, LUA_REGISTRYINDEX);
}
LuaRef::LuaRef(lua_State *l, std::string name) : mRef(LUA_REFNIL), mState(l) {
    lua_getglobal(l, name.c_str());
    mRef = luaL_ref(mState, LUA_REGISTRYINDEX);
}
LuaRef::~LuaRef(){
    luaL_unref(mState, LUA_REGISTRYINDEX, mRef);
}
void LuaRef::Push(){
    lua_rawgeti(mState, LUA_REGISTRYINDEX, mRef);
}
