#include <luabind/luabind.hpp>
#include "luamodule.h"

LuaModule::LuaModule(int (*registerFunc)(lua_State*)) : mRegistered(false){
    mRegisterFunc = registerFunc;
}
LuaModule::LuaModule() : mRegistered(false){
}
int LuaModule::Register(lua_State *l){
    if (!mRegistered){
        mRegistered = true;
        return mRegisterFunc(l);
    }
    return 0;
}