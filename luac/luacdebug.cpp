#include <string>
#include <lua.hpp>
#include "src/debug.h"
#include "luacdebug.h"

#include "luacscript.h"

const std::string LuaC::DebugLib::sClassName = "Debug";

int LuaC::DebugLib::luaopen_debug(lua_State *l){
    //Stack: lib name
    //For debug we just want to create a global table with the classname
    //and push our functions onto it
    lua_newtable(l);
    //Stack: lib name, table
    lua_pushcfunction(l, log);
    //Stack: lib name, table, fcn
    lua_setfield(l, -2, "log");
    //Stack: lib name, table
    //Set the table with the global name of the classname
    lua_setglobal(l, sClassName.c_str());
    return 0;
}
int LuaC::DebugLib::log(lua_State *l){
    LuaScriptLib::stackDump(l);
    //Stack: table, string to log
    std::string str = luaL_checkstring(l, 1);
    Debug::Log(str);
    return 0;
}