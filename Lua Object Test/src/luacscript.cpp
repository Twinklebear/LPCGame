#include <string>
#include <map>
#include <iostream>
#include <fstream>
#include <lua.hpp>
#include "luarect.h"
#include "vectors.h"
#include "luacscript.h"
#include "luaprimitiveparam.h"

//Static data
const LuaCScript::TRegisterMap LuaCScript::sRegisterFuncs = LuaCScript::CreateMap();
const LuaCScript::TAdderMap LuaCScript::sTableAdders = LuaCScript::createAdderMap();
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
        AddLoader(&LuaCScript::requireModule);
        AddLoader(&LuaCScript::requireScript);
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
int LuaCScript::requireModule(lua_State *l){
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
int LuaCScript::requireScript(lua_State *l){
    //Check if the script is an engine script, if yes push DoScript, if no error
    std::string script = lua_tostring(l, -1);
    if (script.substr(0, 7) == "scripts"){
        std::string scriptFile = "../res/" + script;
        std::ifstream checkFile(scriptFile.c_str());
        if (checkFile.good()){
            checkFile.close();
            lua_pushstring(l, scriptFile.c_str());
            lua_pushcfunction(l, LuaCScript::doScript);
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
int LuaCScript::doScript(lua_State *l){
    std::string script = lua_tostring(l, 0);
    luaL_dofile(l, script.c_str());
    //Stack still has the initial string we called with scripts/blah, so remove it
    lua_pop(l, 1);
    return 0;
}
LuaCScript::TRegisterMap LuaCScript::CreateMap(){
    TRegisterMap map;
    map["LuaCScript"] = &LuaCScript::luaopen_luacscript;
    map["LuaRect"]    = &LuaRect::luaopen_luarect;
    map["Vector2f"]   = &Vector2<float>::luaopen_vector2f;
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
LuaCScript::TAdderMap LuaCScript::createAdderMap(){
    TAdderMap map;
    map["LuaRect"]    = &LuaRect::addLuaRect;
    map["LuaCScript"] = &LuaCScript::addLuaCScript;
    map["Vector2f"]   = &Vector2f::addVector2f;
    return map;
}
int LuaCScript::callFunction(lua_State *caller){
    /**
    *  We are given a caller stack with:
    *  userdata      - the LuaCScript** we want to call function on
    *  function name - function to call
    *  # results     - # results (can't call function properly without this)
    *  params        - the params to passs
    */
    //Get the lua_State* of the script we want to call
    lua_State *receiver = (*checkLuaCScript(caller))->Get();
    std::string func = lua_tostring(caller, 2);
    int nRes = lua_tointeger(caller, 3);
    //Remove script udata, function name and # results
    for (int i = 0; i < 3; ++i)
        lua_remove(caller, 1);
    //caller: params
    //# params = stack size of caller
    int nPar = lua_gettop(caller);

    //Print information about the call
    /*
    std::cout << "Calling: " << std::endl
        << "\t'" << func << "'" << std::endl
        << "\t" << nPar << " #params" << std::endl
        << "\t" << nRes << " #results" << std::endl
        << "Remaining stack (params): ";
    stackDump(caller);
    */
    std::vector<std::string> udataTypes = checkUdata(caller);
    //Get the function, we need to get function first because the params
    //are pulled from the top of the stack down, so if function is at top
    //there's nothing to pull
    lua_getglobal(receiver, func.c_str());
    //receiving stack: function
    //Transfer params
    lua_xmove(caller, receiver, nPar);
    //caller stack: empty
    //receiver stack: function, params
    setUdata(receiver, udataTypes);
    //receiving stack: function, params
    //Call the function
    if (lua_pcall(receiver, nPar, nRes, 0) != 0){
        std::cout << "Error calling: " << func << " " << lua_tostring(receiver, -1) << std::endl;
        return 0;
    }
    //If call success receiving stack now contains nRes results
    //Parse the stack for udata types
    udataTypes = checkUdata(receiver);
    //Push the results back
    lua_xmove(receiver, caller, nRes);
    //Register the udata types
    setUdata(caller, udataTypes);
    /**
    *  Final Stacks:
    *  caller stack: results
    *  receiver stack: empty
    */
    //Return # res that caller should pick up
    return nRes;
}
std::vector<std::string> LuaCScript::checkUdata(lua_State *l){
    //l stack: params
    //We want to step through and record the typenames of the userdata
    std::vector<std::string> udata;
    for (int i = 1, top = lua_gettop(l); i <= top; ++i){
        int t = lua_type(l, i);
        std::string luaTName = lua_typename(l, t);
        //If we find some userdata, read the type and store it
        if (luaTName == "userdata")
            udata.push_back(readType(l, i));
    }
    return udata;
}
std::string LuaCScript::readType(lua_State *l, int i){
    //Stack: some # of params, i corresponds to the udata we want to identify
    std::string type = "";
    //Get the metatable of udata at index i
    if (lua_getmetatable(l, i)){
        //Stack: stuff, udata's metatable
        //Get the "type" field
        lua_getfield(l, -1, "type");
        //Stack: stuff, udata metatable, typename
        //Get the type from the stack
        type = luaL_checkstring(l, -1);
    }
    //Stack: stuff, udata metatable, typename
    //Stack contains the typename and its metatable, pop them off
    lua_pop(l, 2);
    return type;
}
void LuaCScript::setUdata(lua_State *l, std::vector<std::string> udata){
    //l stack: params
    //Step through and find udata, and register it according to the value at the vector
    //after each registration, increment vector pos
    std::vector<std::string>::const_iterator iter = udata.begin();
    for (int i = 1, top = lua_gettop(l); i <= top; ++i){
        int t = lua_type(l, i);
        std::string luaTName = lua_typename(l, t);
        //If we find some userdata, read the type and register it accordingly
        if (luaTName == "userdata"){
            sTableAdders.at(*iter)(l, (i - top - 1));
            ++iter;
        }
    }
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
            //Other (userdata)
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
    { "name", name },
    { "open", open },
    { NULL, NULL }
};
int LuaCScript::luaopen_luacscript(lua_State *l){
    //Stack: lib name
    //Push new metatable to hold fcns onto stack
    luaL_newmetatable(l, "LPC.LuaCScript");
    //Stack: lib name, metatable
    //Copy it to the top
    lua_pushvalue(l, -1);
    //Stack: lib name, metatable, metatable
    //Set table at -2 (LPC.LuaCScript) @ key __index to the value at top
    //in this case, the member function table
    lua_setfield(l, -2, "__index");
    //Stack: lib name, metatable
    //Register our member functions into this table
    luaL_register(l, NULL, LuaCScriptLib_m);
    //Pushing on a typename string so we can ID the metatable
    lua_pushstring(l, "LuaCScript");
    //Stack: lib name, metatable, string
    lua_setfield(l, -2, "type");
    //register the non-member functions as well into a global table
    lua_newtable(l);
    //Stack: lib name, metatable
    //Register our global LuaCScript fcns into this table
    luaL_register(l, NULL, LuaCScriptLib_f);
    //Push the table onto the global stack with a name
    lua_setglobal(l, "LuaCScript");
    //Stack: lib name, metatable
    return 1;
}
LuaCScript** LuaCScript::checkLuaCScript(lua_State *l, int i){
    return (LuaCScript**)luaL_checkudata(l, i, "LPC.LuaCScript");
}
void LuaCScript::addLuaCScript(lua_State *l, int i){
    //Get the metatable. With one item on our stack (the udata)
    luaL_getmetatable(l, "LPC.LuaCScript");
    //Now the metatable is at the top of the stack and our
    //udata is at -2 so we set the data there to use the metatable
    lua_setmetatable(l, i - 1);
}
int LuaCScript::getScript(lua_State *l){
    //Stack: script name
    std::string script = lua_tostring(l, 1);
    lua_remove(l, 1);
    //Stack: empty
    //Create a new LuaCScript** udata in the state, this pointer will point
    //to the LuaCScript pointer in the map
    LuaCScript **sPush = (LuaCScript**)lua_newuserdata(l, sizeof(LuaCScript*));
    //Stack: udata
    //Set the sPush to the script wanted
    *sPush = GetScript(script);
    //Register it with the metatable
    addLuaCScript(l, -1);
    return 1;
}
int LuaCScript::name(lua_State *l){
    //Stack: udata
    //Check the udata and push its name back
    LuaCScript **s = checkLuaCScript(l);
    lua_pop(l, 1);
    std::string name = (*s)->Name();
    //Push the name onto stack to return
    lua_pushstring(l, name.c_str());
    return 1;
}
int LuaCScript::open(lua_State *l){
    //Stack: udata
    //Check the udata and push the value of open back
    LuaCScript **s = checkLuaCScript(l);
    lua_pop(l, 1);
    lua_pushboolean(l, (*s)->Open());
    return 1;
}