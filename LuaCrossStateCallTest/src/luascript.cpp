#include <string>
#include <fstream>
#include <lua.hpp>
#include <luabind/luabind.hpp>
#include "vectors.h"
#include "luarect.h"
#include "luascript.h"

static void stackDump(lua_State *l){
    std::cout << "Lua Stack Dump: ";
    for (int i = 1, top = lua_gettop(l); i <= top; ++i){
        int t = lua_type(l, i);
        std::cout <<"@" << i << ": ";
        switch (t) {
            //Strings
            case LUA_TSTRING:
                std::cout << lua_tostring(l, i);
                break;
            //Bools
            case LUA_TBOOLEAN:
                std::cout << (lua_toboolean(l, i) ? "True" : "False");
                break;
            //Numbers
            case LUA_TNUMBER:
                std::cout << lua_tonumber(l, i);
                break;
            //Other (userdata and such)
            default:
                std::cout << lua_typename(l, t);
                break;
        }
        std::cout << ", ";
    }
    std::cout << std::endl;
}
static int GenericCall(lua_State *l){
    //Get function name
    int top = lua_gettop(l);
    std::cout << "Stack size: " << top << std::endl;
    stackDump(l);
    std::string funcName = lua_tostring(l, 1);
    std::cout << "--Generic Call Function--\n\t" << funcName << std::endl;
    //Get # params
    int nParams = lua_tointeger(l, 2);
    std::cout << "\t" << nParams << " params" << std::endl;
    int nResults = lua_tointeger(l, 3);
    std::cout << "\t" << nResults << " results" << std::endl;
    std::cout << "-------------------------" << std::endl;
    
    //Remove the function name, nParams and nResults from the stack
    for (int i = 0; i < 3; ++i)
        lua_remove(l, 1);

    top = lua_gettop(l);
    std::cout << "Clearing fName, nParams & nResults, new stack size: " << top << std::endl;
    stackDump(l);

    //Get the target lua script, gets me nothing..
    //LuaScript *script = (LuaScript*)lua_touserdata(l, -top);

    std::string targName = lua_tostring(l, 1);
    //std::string targName = script->Name();
    std::cout << "Script Name: " << targName << std::endl;
    lua_remove(l, 1);

    lua_State* stateFromLookup = LuaScript::GetScript(targName)->Get();
    
    //Get the function to call
    lua_getglobal(stateFromLookup, funcName.c_str());
    //Transfer the params
    lua_xmove(l, stateFromLookup, nParams);
    //Call the function
    if (lua_pcall(stateFromLookup, nParams, nResults, 0) != 0){
        std::cout << "Error calling: " << funcName << lua_tostring(stateFromLookup, -1) << std::endl;
        return 0;
    }
    //Push results back
    lua_xmove(stateFromLookup, l, nResults);
    return nResults;
}

//Setup the unordered_map
const LuaScript::TRegisterLuaMap LuaScript::mRegisterLuaFunc = LuaScript::CreateMap();
LuaScript::TScriptMap LuaScript::sScriptMap;

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
        //Add it to the map
        sScriptMap[Name()] = this;
    }
}
LuaScript* LuaScript::GetScript(const std::string &name){
    TScriptMap::const_iterator found = sScriptMap.find(name);
    if (found != sScriptMap.end()){
        return sScriptMap[name];
    }
    std::cout << "LuaScript::GetScript Error: " << name
        << " couldn't be found" << std::endl;
    return NULL;
}
void LuaScript::CallFunction(const std::string &func){
    if (!Open()){
        std::cout << "CallFunction: " << func << " Error: No script open!" << std::endl;
        return;
    }
    //Get the function
    lua_getglobal(mL, func.c_str());
    //Try to call it
    if (lua_pcall(mL, 0, 0, 0) != 0){
        std::cout << "Error calling: " << func
            << " - " << lua_tostring(mL, -1) << std::endl;
    }
}
void LuaScript::CallFunction(lua_State *l, const std::string &func, int nParam, int nRes){
    //Get the function
    lua_getglobal(mL, func.c_str());
    //need to pop off the nParam and nRes values
    int p = lua_tointeger(l, -2);
    int r = lua_tointeger(l, -1);
    //lua_pop(l, -1);
    //lua_pop(l, -2);
    std::cout << "p: " << p << " r: " << r << std::endl;

    //Try getting something from top of stack
    std::string str = lua_tostring(l, -3);
    //lua_pop(l, 2);
    std::cout << "I got: " << str << std::endl;

    //Try to get the LuaScript
    std::cout << "Trying to get LuaScript - stack[1]" << std::endl;
    LuaScript* lScript = (LuaScript*)lua_touserdata(l, 1);
    std::cout << "Script: " << lScript->File()
        << " open: " << (lScript->Open() ? "True" : "False")<< std::endl;

    //Perform a stack dump
    stackDump(l);

    //push the params from the stack: Will this work?
    //How can i move the values I want onto the top of the stack so they'll be pulled?
    //ie. into indices 3..nParam?
    lua_xmove(l, mL, nParam);
    //Try to call function
    if (lua_pcall(mL, nParam, nRes, 0) != 0){
        std::cout << "Error calling: " << func
            << " - " << lua_tostring(mL, -1) << std::endl;
        return;
    }
    //Push results back
    lua_xmove(mL, l, nRes);
}
void LuaScript::Close(){
    if (Open()){
        lua_close(mL);
        mL = nullptr;
    }
}
LuaScript::TRegisterLuaMap LuaScript::CreateMap(){
    TRegisterLuaMap map;
    map["LuaScript"]     = &LuaScript::RegisterLua;
    map["Vector2"]       = &Vector2f::RegisterLua;
    map["LuaRect"]       = &LuaRect::luaopen_luarect;
    return map;
}
int LuaScript::RequireModule(lua_State *l){
    //Get the module name
    std::string module = lua_tostring(l, -1);
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
    std::string script = lua_tostring(l, -1);
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
    return 1;
}
lua_State* LuaScript::Get(){
	return mL;
}
std::string LuaScript::File() const {
	return mFile;
}
std::string LuaScript::Name() const {
    size_t sPos = mFile.find_last_of('/');
    size_t length = (mFile.find_last_of('.') - 1) - sPos;
    return mFile.substr(sPos + 1, length);
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
int LuaScript::RegisterLua(lua_State *l){
    using namespace luabind;

    module(l, "LPC")[
        class_<LuaScript>("LuaScript")
            .def(constructor<>())
            .def("CallFunction", (void (LuaScript::*)(const std::string&))&LuaScript::CallFunction)
            .def("CallFunction", (void (LuaScript::*)(lua_State*, const std::string&, int, int))&LuaScript::CallFunction)
            .def("Name", &LuaScript::Name)
            .def("File", &LuaScript::File)
            .scope[
                def("GetScript", &LuaScript::GetScript)
            ]
    ];
    //Push our function
    lua_pushcfunction(l, &GenericCall);
    lua_setglobal(l, "GenericCall");

    return 0;
}
