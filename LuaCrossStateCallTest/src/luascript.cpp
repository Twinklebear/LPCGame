#include <string>
#include <fstream>
#include <lua.hpp>
#include <luabind/luabind.hpp>
#include "vectors.h"
#include "luascript.h"

//Setup the unordered_map
const LuaScript::TRegisterLuaMap LuaScript::mRegisterLuaFunc = LuaScript::CreateMap();

LuaScript::LuaScript() : mL(nullptr), mFile(""){
}
LuaScript::LuaScript(std::string script) : mL(nullptr), mFile(""){
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
        luabind::open(mL);
        AddLoaders();
        luaL_dofile(mL, mFile.c_str());
    }
}
void LuaScript::Close(){
    if (Open()){
        lua_close(mL);
        mL = nullptr;
    }
}
LuaScript::TRegisterLuaMap LuaScript::CreateMap(){
    TRegisterLuaMap map;
    map["Vector2"]       = &Vector2f::RegisterLua;
    return map;
}
int LuaScript::RequireModule(lua_State *l){
    //Get the module name
    std::string module = lua_tostring(l, 1);
    //Check if the module name is in the unordered_map
    TRegisterLuaMap::const_iterator found = mRegisterLuaFunc.find(module);
    //If the module requested exists push the registration function on the stack
    if (found != mRegisterLuaFunc.end()){
        lua_pushcfunction(l, mRegisterLuaFunc.at(module));
    }
    else {
        std::string err = "\n\tRequireModule Error: failed to find: " + module + "\n";
        std::cout << err << std::endl;
        lua_pushstring(l, err.c_str());
    }
    return 1;
}
int LuaScript::RequireScript(lua_State *l){
    //Get the script name and check if it's an engine script
    //ie. the name is scripts/*
    std::string script = lua_tostring(l, 1);
    if (script.substr(0, 7) == "scripts"){
        std::string scriptFile = "../res/" + script;
        //If it exists push DoScript onto the stack, if not error
        std::ifstream checkFile(scriptFile.c_str());
        if (checkFile.good()){
            checkFile.close();
            //push the full path back onto the stack for DoScript to use
            lua_pushstring(l, scriptFile.c_str());
            lua_pushcfunction(l, LuaScript::DoScript);
        }
        else {
            std::string err = "RequireScript Error: Failed to find" + scriptFile;
            std::cout << err << std::endl;
            lua_pushstring(l, err.c_str());
        }
    }
    return 1;
}
int LuaScript::DoScript(lua_State *l){
    //Get the filename and dofile
    std::string script = lua_tostring(l, 0);
    luaL_dofile(l, script.c_str());
    //pop the string off the stack
    lua_pop(l, 0);
    return 1;
}
lua_State* LuaScript::Get(){
	return mL;
}
std::string LuaScript::File() const {
	return mFile;
}
bool LuaScript::Open() const {
	return (mL != nullptr);
}
void LuaScript::AddModuleLoader(){
    //Get the packages table
    lua_getfield(mL, LUA_GLOBALSINDEX, "package");
    //Get the loaders table
    lua_getfield(mL, -1, "loaders");
    //Get rid of the packages table
    lua_remove(mL, -2);

    //Count # of loaders
    int numLoaders = 0;
    lua_pushnil(mL);
    while (lua_next(mL, -2) != 0){
        lua_pop(mL, 1);
        ++numLoaders;
    }
    //Add our function
    lua_pushinteger(mL, numLoaders + 1);
    lua_pushcfunction(mL, &LuaScript::RequireModule);
    lua_rawset(mL, -3);
    //Free table from stack
    lua_pop(mL, 1);
}
void LuaScript::AddScriptLoader(){
    //Get the packages table
    lua_getfield(mL, LUA_GLOBALSINDEX, "package");
    //Get the loaders table
    lua_getfield(mL, -1, "loaders");
    //Get rid of the packages table
    lua_remove(mL, -2);
    
    //Count # of loaders
    int numLoaders = 0;
    lua_pushnil(mL);
    while (lua_next(mL, -2) != 0){
        lua_pop(mL, 1);
        ++numLoaders;
    }
    //Add our function
    lua_pushinteger(mL, numLoaders + 1);
    lua_pushcfunction(mL, &LuaScript::RequireScript);
    lua_rawset(mL, -3);
    //Free table from stack
    lua_pop(mL, 1);
}
void LuaScript::AddLoaders(){
    AddScriptLoader();
    AddModuleLoader();
}