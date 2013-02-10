#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <lua.hpp>
#include "external/json/json.h"
#include "luac/luacscript.h"
#include "luac/luacfunctioninterface.h"
#include "debug.h"
#include "luascript.h"

LuaScript::LuaScript() : mL(nullptr), mFile(""), mOpen(false) {
}
LuaScript::LuaScript(std::string script) : mL(nullptr), mFile(""), mOpen(false) {
    OpenScript(script);
}
LuaScript::~LuaScript(){
    Close();
}
void LuaScript::OpenScript(const std::string &script){
    //If the new script name is valid, open it
    if (script != ""){
        //Close currently open script if one is open
        Close();
        mFile = script;
        mL = lua_open();
        luaL_openlibs(mL);
        AddLoader(LuaC::LuaScriptLib::requireLib);
        AddLoader(LuaC::LuaScriptLib::requireScript);
        luaL_dofile(mL, mFile.c_str());
        mOpen = true;
        //Setup function interface
        mFcnInterface = LuaC::FunctionInterface(mL, mFile);
    }
}
void LuaScript::Close(){
    if (Open()){
        //CallFunction("Free");
        mFcnInterface.CallFunction<void>("Free");
        lua_close(mL);
        mL = NULL;
        mOpen = false;
    }
}
lua_State* LuaScript::Get(){
	return mL;
}
std::string LuaScript::File() const {
	return mFile;
}
bool LuaScript::Open() const {
	return mOpen;
}
void LuaScript::AddLoader(int (*loader)(lua_State*)){
    //We want to get the package.loaders table and add a new entry
    lua_getfield(mL, LUA_GLOBALSINDEX, "package");
    //Stack: package table
    //Get the loaders table
    lua_getfield(mL, -1, "loaders");
    //Stack: package table, loaders table
    //Remove the package table
    lua_remove(mL, -2);
    //Stack: loaders table

    //Count the # of loaders
    int n = 0;
    //We push nil so we can know when we hit the end
    lua_pushnil(mL);
    //Go through the loaders table and count # entries
    while (lua_next(mL, -2) != 0){
        lua_pop(mL, 1);
        ++n;
    }
    //Stack: loaders table
    //Add our function
    lua_pushinteger(mL, n + 1);
    //Stack: loaders table, index to add fcn to
    lua_pushcfunction(mL, loader);
    //Stack: loaders table, index to add fcn to, fcn
    //Add it to the loaders table
    lua_rawset(mL, -3);
    //Stack: loaders table
    //Pop the table off
    lua_pop(mL, 1);
}
LuaC::FunctionInterface* LuaScript::FunctionInterface(){
    return &mFcnInterface;
}