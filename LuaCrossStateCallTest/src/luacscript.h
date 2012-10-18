#ifndef LUACSCRIPT
#define LUACSCRIPT

#include <string>
#include <map>
#include <lua.hpp>

///A version of the LuaScript class written with the Lua C API
class LuaCScript {
public:
    //Class member functions
    LuaCScript();
    LuaCScript(std::string script);
    void Open(std::string script);
    lua_State* Get();
    std::string File() const;
    std::string Name() const;
    bool Open() const;

private:
    //Private members
    void Close();
    void AddLoader(int (*loader)(lua_State*));

private:
    lua_State *mL;
    std::string mFile;

private:
    //Stuff to interface with Lua, hidden from C++
    //Functions for require modules and scripts
    static int RequireModule(lua_State *l);
    static int RequireScript(lua_State *l);
    static int DoScript(lua_State *l);
    //The map of module loaders type and its creator
    typedef std::map<std::string, int(*)(lua_State*)> TRegisterMap;
    static TRegisterMap CreateMap();
    //The script map for lookups
    typedef std::map<std::string, LuaCScript*> TCScriptMap;
    //Script Lookup function
    static LuaCScript* GetScript(const std::string &name);
    //For calling functions on some lua script
    static int CallFunction(lua_State *l);
    //Perform a stack dump on a state
    static int StackDump(lua_State *l);

private:
    //The Lua C functions
    static const struct luaL_reg LuaCScriptLib_f[];
    //The Lua C member functions
    static const struct luaL_reg LuaCScriptLib_m[];
    //The registration function
    static int luaopen_luacscript(lua_State *l);
    //Some other necesary member functions
    static LuaCScript** CheckLuaCScript(lua_State *l);
    static void UpdateMetaTable(lua_State *l);
    static int AddLuaCScript(lua_State *l);
    static int GetScript(lua_State *l);
    static int Name(lua_State *l);
    static int Open(lua_State *l);
    

private:
    static const TRegisterMap sRegisterFuncs;
    static TCScriptMap sScriptMap;
};

#endif