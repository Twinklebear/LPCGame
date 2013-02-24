#include <string>
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
        //Release references
        mReferences.clear();
        lua_close(mL);
        mL = NULL;
        mOpen = false;
    }
}
void LuaScript::Reference(std::string name){
    mReferences[name] = LuaC::LuaRef(mL, name);
}
void LuaScript::Reference(std::string table, std::string field){
    //Check if we've got a reference to the table
    std::map<std::string, LuaC::LuaRef>::const_iterator fnd = 
        mReferences.find(table);
    if (fnd != mReferences.end()){
        fnd->second.Push(mL);
        //Get the field desired and store a reference to it
        lua_getfield(mL, -1, field.c_str());
        mReferences[field] = LuaC::LuaRef(mL, -1);
    }
    //If we don't have the table referenced try to get it as a global
    else {
        lua_getglobal(mL, table.c_str());
        lua_getfield(mL, -1, field.c_str());
        mReferences[field] = LuaC::LuaRef(mL, -1);
    }
    //Pop the table and function off the stack
    lua_pop(mL, 2);
}
LuaC::LuaRef LuaScript::GetReference(std::string name){
    //Lookup the reference in the map
    std::map<std::string, LuaC::LuaRef>::const_iterator fnd = 
        mReferences.find(name);
    if (fnd != mReferences.end())
        return fnd->second;
    //If we didn't find it, return blank reference, ie. LUA_REFNIL
    return LuaC::LuaRef();
}
lua_State* LuaScript::Get(){
	return mL;
}
std::string LuaScript::File() const {
	return mFile;
}
std::string LuaScript::TableName() const {
    //We want the actual filename, without the extension, this is found
    //between the final '/' and the final '.'
    size_t start = mFile.find_last_of('/') + 1;
    size_t length = mFile.find_last_of('.') - start;
    return mFile.substr(start, length);
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