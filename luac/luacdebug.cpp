#include <string>
#include <lua.hpp>
#include "src/debug.h"
#include "luacdebug.h"

#include "luacscript.h"

const std::string LuaC::DebugLib::sClassName = "Debug";

int LuaC::DebugLib::luaopen_debug(lua_State *l){
    //Stack: lib name
    //Register the library as a global table "Debug"
    luaL_register(l, sClassName.c_str(), luaDebugLib);
    return 0;
}
const struct luaL_reg LuaC::DebugLib::luaDebugLib[] = {
    { "log", log },
    { NULL, NULL }
};
int LuaC::DebugLib::log(lua_State *l){
    LuaScriptLib::stackDump(l);
    //Stack: table, string to log
    std::string str = luaL_checkstring(l, 1);
    Debug::Log(str);
    return 0;
}