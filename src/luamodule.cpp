#include <luabind/luabind.hpp>
#include "luamodule.h"

LuaModule::LuaModule(void (*registerFunc)(lua_State*)) : mRegistered(false){
    mRegisterFunc = registerFunc;
}
LuaModule::LuaModule() : mRegistered(false){
}
void LuaModule::Register(lua_State *l){
    if (!mRegistered){
        mRegisterFunc(l);
        mRegistered = true;
    }
}
