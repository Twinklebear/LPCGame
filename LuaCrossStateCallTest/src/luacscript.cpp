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
    //Stack still has the initial string we called with scripts/blah, so remove it
    lua_pop(l, 1);
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
int LuaCScript::callFunction(lua_State *l){
    /**
    *  We are given a stack with:
    *  userdata      - the LuaCScript** we want to call function on
    *  function name - function to call
    *  # params      - # params
    *  # results     - # results
    *  params        - the params to passs
    */
    //Get the lua_State* of the script we want to call
    lua_State *receiving = (*checkLuaCScript(l))->Get();
    //Pop off the script udata
    lua_remove(l, 1);
    //l stack: Function name, # params, # results, params
    std::string func = lua_tostring(l, 1);
    int nPar = lua_tointeger(l, 2);
    int nRes = lua_tointeger(l, 3);
    //Remove function name, # params, # results and udata signature
    for (int i = 0; i < 3; ++i)
        lua_remove(l, 1);
    //l stack: params to pass

    //Print information about the call
    std::cout << "Calling: " << std::endl
        << "\t'" << func << "'" << std::endl
        << "\t" << nPar << " #params" << std::endl
        << "\t" << nRes << " #results" << std::endl
        << "Remaining stack (params): ";
    stackDump(l);

    //TESTING ASSUMPTION FOR TESTING ONLY
    //The final item on stack will be udata, so check its type
    std::string udataType = readType(l, -1);

    //Get the function, we need to get function first because the params
    //are pulled from the top of the stack down, so if function is at top
    //there's nothing to pull
    lua_getglobal(receiving, func.c_str());
    //receiving stack: function
    //Transfer params
    lua_xmove(l, receiving, nPar);
    //l stack: empty
    //receiving stack: function, params
    stackDump(receiving);
    if (udataType == "LuaRect"){
        LuaRect::addLuaRect(receiving, -1);
    }
    //receiving stack: function, params
    //Call the function
    if (lua_pcall(receiving, nPar, nRes, 0) != 0){
        std::cout << "Error calling: " << func << " " << lua_tostring(receiving, -1) << std::endl;
        return 0;
    }
    //If call success receiving stack now contains nRes results
    //Push the results back
    lua_xmove(receiving, l, nRes);
    /**
    *  Final Stacks:
    *  l stack: results
    *  receiving stack: empty
    */
    stackDump(l);
    stackDump(receiving);
    //Return # res that l should pick up
    return nRes;
}
std::string LuaCScript::readType(lua_State *l, int i){
    std::cout << "Trying to read type: ";
    stackDump(l);
    std::string type = "";
    //Get the metatable of udata at index i
    if (lua_getmetatable(l, i)){
        stackDump(l);
        //Get the "type" field
        lua_getfield(l, -1, "type");
        stackDump(l);
        //Call the function
        lua_pcall(l, 0, 1, 0);
        stackDump(l);
        //Get the type from the stack
        type = luaL_checkstring(l, -1);
        std::cout << "Read type: " << type << std::endl;
        stackDump(l);
    }
    //Stack contains the typename and its metatable, pop them off
    lua_pop(l, 2);
    return type;
}
int LuaCScript::stackDump(lua_State *l){
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
    { "getScript", getScript },
    { NULL, NULL }
};
const struct luaL_reg LuaCScript::LuaCScriptLib_m[] = {
    { "callFunction", callFunction },
    { "stackDump", stackDump },
    { "name", name },
    { "open", open },
    { NULL, NULL }
};
int LuaCScript::luaopen_luacscript(lua_State *l){
    //Push new metatable to hold fcns onto stack
    luaL_newmetatable(l, "LPC.LuaCScript");
    //Copy it to the top
    lua_pushvalue(l, -1);
    //Set table at -2 (LPC.LuaCScript) @ key __index to the value at top
    //in this case, the member function table
    lua_setfield(l, -2, "__index");
    //Register our member functions into this table
    luaL_register(l, NULL, LuaCScriptLib_m);
    //register the non-member functions as well
    luaL_register(l, "LuaCScript", LuaCScriptLib_f);
    return 1;
}
LuaCScript** LuaCScript::checkLuaCScript(lua_State *l){
    return (LuaCScript**)luaL_checkudata(l, 1, "LPC.LuaCScript");
}
void LuaCScript::updateMetaTable(lua_State *l){
    //Get the metatable. With one item on our stack (the udata)
    luaL_getmetatable(l, "LPC.LuaCScript");
    //Now the metatable is at the top of the stack and our
    //udata is at -2 so we set the data there to use the metatable
    lua_setmetatable(l, -2);
}
int LuaCScript::addLuaCScript(lua_State *l){
    LuaCScript **s = (LuaCScript**)lua_touserdata(l, 1);
    luaL_argcheck(l, *s != NULL, 1, "LuaCScript Expected");
    updateMetaTable(l);
    return 0;
}
int LuaCScript::getScript(lua_State *l){
    std::string script = lua_tostring(l, 1);
    lua_remove(l, 1);
    LuaCScript *s = GetScript(script);
    LuaCScript **sPush = (LuaCScript**)lua_newuserdata(l, sizeof(LuaCScript*));
    *sPush = s;
    updateMetaTable(l);
    return 1;
}
int LuaCScript::name(lua_State *l){
    LuaCScript **s = checkLuaCScript(l);
    std::string name = (*s)->Name();
    lua_pushstring(l, name.c_str());
    return 1;
}
int LuaCScript::open(lua_State *l){
    LuaCScript **s = checkLuaCScript(l);
    lua_pushboolean(l, (*s)->Open());
    return 1;
}
