#ifndef LUAMODULE_H
#define LUAMODULE_H

#include <luabind/luabind.hpp>

///Describes a Lua module and provides some safety
/**
*  A simple class to describe a a Lua module and provides
*  some safety checking to prevent double-registration of modules
*/
class LuaModule {
public:
    /**
    *  Create the LuaModule passing it the function to register the module with
    *  @param moduleFunc The module's registration function
    */
    LuaModule(int (*registerFunc)(lua_State*));
    LuaModule();
    /**
    *  Register the module to some lua_State
    *  @param l The lua_State to register with
    */
    int Register(lua_State *l);

private:
    ///The module registration function
    int (*mRegisterFunc)(lua_State*);
    ///For tracking if the module is already registered
    bool mRegistered;
};

#endif