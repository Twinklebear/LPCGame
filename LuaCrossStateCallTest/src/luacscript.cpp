#include <string>
#include <map>
#include <iostream>
#include <fstream>
#include <lua.hpp>
#include "luarect.h"
#include "luacscript.h"

//Static data
const LuaCScript::TRegisterMap LuaCScript::sRegisterFuncs = LuaCScript::CreateMap();
LuaCScript::TCScriptMap LuaCScript::sScriptMap;

LuaCScript::LuaCScript()
    : mL(nullptr), mFile("")
{
}
LuaCScript::LuaCScript(std::string script)
    : mL(nullptr), mFile("")
{
    Open(script);
}
void LuaCScript::Open(std::string script){
    if (script != ""){
        if (Open())
            Close();
        mFile = script;
        mL = lua_open();
        luaL_openlibs(mL);
        AddLoader(&LuaCScript::RequireModule);
        AddLoader(&LuaCScript::RequireScript);
        luaL_dofile(mL, mFile.c_str());
        sScriptMap[Name()] = this;
    }
    else
        std::cout << "LuaCScript Error: No script filename" << std::endl;
}
lua_State* LuaCScript::Get(){
    return mL;
}
std::string LuaCScript::File() const {
    return mFile;
}
std::string LuaCScript::Name() const {
    size_t sPos = mFile.find_last_of('/');
    size_t length = (mFile.find_last_of('.') - 1) - sPos;
    return mFile.substr(sPos + 1, length);
}
bool LuaCScript::Open() const {
    return (mL != nullptr);
}
void LuaCScript::Close(){
    if (Open())
        lua_close(mL);
    mL = nullptr;
    mFile = "";
}
void LuaCScript::AddLoader(int (*loader)(lua_State*)){
    //Get the package.loaders table
    lua_getfield(mL, LUA_GLOBALSINDEX, "package");
    lua_getfield(mL, -1, "loaders");
    lua_remove(mL, -2);
    //Count the # of loaders
    int n = 0;
    lua_pushnil(mL);
    while (lua_next(mL, -2) != 0){
        lua_pop(mL, 1);
        ++n;
    }
    //Add our function
    lua_pushinteger(mL, n + 1);
    lua_pushcfunction(mL, loader);
    lua_rawset(mL, -3);
    //Pop the table off
    lua_pop(mL, 1);
}
int LuaCScript::RequireModule(lua_State *l){
    //Try to look up the module desired, if it's one of ours load it, if not error
    std::string module = lua_tostring(l, -1);
    TRegisterMap::const_iterator fnd = sRegisterFuncs.find(module);
    if (fnd != sRegisterFuncs.end())
        lua_pushcfunction(l, sRegisterFuncs.at(module));
    else {
        std::string err = "LuaCScript::RequireModule Error: Failed to find: "
            + module + "\n";
        lua_pushstring(l, err.c_str());
    }
    return 1;
}
int LuaCScript::RequireScript(lua_State *l){
    //Check if the script is an engine script, if yes push DoScript, if no error
    std::string script = lua_tostring(l, -1);
    if (script.substr(0, 7) == "scripts"){
        std::string scriptFile = "../res/" + script;
        std::ifstream checkFile(scriptFile.c_str());
        if (checkFile.good()){
            checkFile.close();
            lua_pushstring(l, scriptFile.c_str());
            lua_pushcfunction(l, LuaCScript::DoScript);
        }
        else {
            std::string err = "LuaCScript::RequireScript Error: Failed to find: " 
                + scriptFile + "\n";
            std::cout << err << std::endl;
            lua_pushstring(l, err.c_str());
        }
    }
    //If not an engine script, nothing to return
    else 
        return 0;
    //If we found script or failed to load engine script we've got a result to return
    return 1;
}
int LuaCScript::DoScript(lua_State *l){
    std::string script = lua_tostring(l, 0);
    luaL_dofile(l, script.c_str());
    return 1;
}
LuaCScript::TRegisterMap LuaCScript::CreateMap(){
    TRegisterMap map;
    map["LuaCScript"] = &LuaCScript::luaopen_luacscript;
    map["LuaRect"]    = &LuaRect::luaopen_luarect;
    return map;
}
LuaCScript* LuaCScript::GetScript(const std::string &name){
    TCScriptMap::const_iterator fnd = sScriptMap.find(name);
    if (fnd != sScriptMap.end())
        return sScriptMap[name];
    std::cout << "LuaCScript::GetScript Error: Couldn't find: "
        << name << std::endl;
    return NULL;
}
int LuaCScript::CallFunction(lua_State *l){
    /**
    *  We are given a stack like:
    *  userdata        - the LuaCScript** we want to call function on
    *  function name   - function to call
    *  # params        - # params
    *  # results       - # results
    *  udata signature - tells us which metatables to register the udata with in target state
    *  params          - the params to passs
    */
    //Get the LuaCScript to call
    LuaCScript **script = CheckLuaCScript(l);
    //Pop off the script udata
    lua_remove(l, 1);
    //Stack: Function name, # params, # results, udata signature, params
    //Get function name, # params and # results
    std::string func = lua_tostring(l, 1);
    int nPar = lua_tointeger(l, 2);
    int nRes = lua_tointeger(l, 3);
    std::string signature = lua_tostring(l, 4);
    //Remove function name, # params, # results and udata signature
    for (int i = 0; i < 4; ++i)
        lua_remove(l, 1);
    
    std::cout << "Calling: " << std::endl
        << "\t" << (*script)->Name() << ":" << std::endl
        << "\t" << func << " with: " << std::endl
        << "\t" << nPar << " #params" << std::endl
        << "\t" << nRes << " #results" << std::endl
        << "\t" << signature << " udata signature" << std::endl;
    
    //Stack now only should have the params to pass
    std::cout << "Remaining stack (params): ";
    StackDump(l);

    lua_State *scriptState = (*script)->Get();
    //Get the function
    lua_getglobal(scriptState, func.c_str());
    //scriptState stack: function
    //Transfer params
    lua_xmove(l, scriptState, nPar);
    //script state stack: function, params
    //Call the function
    if (lua_pcall(scriptState, nPar, nRes, 0) != 0){
        std::cout << "Error calling: " << func << " " << lua_tostring(scriptState, -1) << std::endl;
        return 0;
    }
    //If call success scriptState stack now contains nRes results
    //Push the results back
    lua_xmove(scriptState, l, nRes);
    /**
    *  Final Stacks:
    *  l: results
    *  scriptState: empty
    */
    StackDump(l);
    StackDump(scriptState);
    //Return # res that l should pick up
    return nRes;
}
int LuaCScript::StackDump(lua_State *l){
    std::cout << "Stack: ";
    for (int i = 1, top = lua_gettop(l); i <= top; ++i){
        int t = lua_type(l, i);
        std::cout << "@" << i << ": ";
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
    return 0;
}
const struct luaL_reg LuaCScript::LuaCScriptLib_f[] = {
    { "GetScript", GetScript },
    { NULL, NULL }
};
const struct luaL_reg LuaCScript::LuaCScriptLib_m[] = {
    { "CallFunction", CallFunction },
    { "StackDump", StackDump },
    { "Name", Name },
    { "Open", Open },
    { NULL, NULL }
};
int LuaCScript::luaopen_luacscript(lua_State *l){
    luaL_newmetatable(l, "LPC.LuaCScript");
    lua_pushvalue(l, -1);
    lua_setfield(l, -2, "__index");
    luaL_register(l, NULL, LuaCScriptLib_m);
    luaL_register(l, "LuaCScript", LuaCScriptLib_f);
    return 1;
}
LuaCScript** LuaCScript::CheckLuaCScript(lua_State *l){
    return (LuaCScript**)luaL_checkudata(l, 1, "LPC.LuaCScript");
}
void LuaCScript::UpdateMetaTable(lua_State *l){
    luaL_getmetatable(l, "LPC.LuaCScript");
    lua_setmetatable(l, -2);
}
int LuaCScript::AddLuaCScript(lua_State *l){
    LuaCScript **s = (LuaCScript**)lua_touserdata(l, 1);
    luaL_argcheck(l, *s != NULL, 1, "LuaCScript Expected");
    UpdateMetaTable(l);
    return 0;
}
int LuaCScript::GetScript(lua_State *l){
    std::string script = lua_tostring(l, 1);
    lua_remove(l, 1);
    LuaCScript *s = GetScript(script);
    LuaCScript **sPush = (LuaCScript**)lua_newuserdata(l, sizeof(LuaCScript*));
    *sPush = s;
    UpdateMetaTable(l);
    return 1;
}
int LuaCScript::Name(lua_State *l){
    LuaCScript **s = CheckLuaCScript(l);
    std::string name = (*s)->Name();
    lua_pushstring(l, name.c_str());
    return 1;
}
int LuaCScript::Open(lua_State *l){
    LuaCScript **s = CheckLuaCScript(l);
    lua_pushboolean(l, (*s)->Open());
    return 1;
}
