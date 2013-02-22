#include <lua.hpp>
#include "luacdata.h"
#include "luaref.h"
#include "luacreflib.h"

LuaC::LuaRef* LuaC::LuaRefLib::Allocate(lua_State *l){
    return nullptr;
}
void LuaC::LuaRefLib::Push(lua_State *l, const LuaRef obj){
    obj.Push(l);
}
void LuaC::LuaRefLib::Push(lua_State *l, const LuaRef obj, std::string name){
    obj.Push(l, name);
}
void LuaC::LuaRefLib::Copy(lua_State *from, int idx, lua_State *too){
}
LuaC::LuaRef* LuaC::LuaRefLib::Check(lua_State *l, int i){
    return nullptr;
}
LuaC::LuaRef LuaC::LuaRefLib::GetCopy(lua_State *l, int i){
    return LuaC::LuaRef();
}