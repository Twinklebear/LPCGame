#ifndef LUACSCRIPT
#define LUACSCRIPT

#include <string>
#include <map>
#include <vector>
#include <lua.hpp>
#include "luaprimitiveparam.h"

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
    template<class ReturnType>
    auto CallFunction(std::string function, 
        std::vector<LuaC::LuaParam*> args = std::vector<LuaC::LuaParam*>()) -> decltype(ReturnType::Retrieve(mL)) 
    {
        //Get the function to be called
        lua_getglobal(mL, function.c_str());
        //Push the parameters onto the stack
        for (LuaC::LuaParam *p : args)
            p->Push(mL);

        //Call the function
        if (lua_pcall(mL, args.size(), 1, 0) != 0)
            std::cout << "Error calling: " + function + " " + lua_tostring(mL, -1) << std::endl;

        return ReturnType::Retrieve(mL);
    }
    void CallFunction(std::string function, std::vector<LuaC::LuaParam*> args = std::vector<LuaC::LuaParam*>()){
        //Get the function to be called
        lua_getglobal(mL, function.c_str());
        //Push the parameters onto the stack
        for (LuaC::LuaParam *p : args)
            p->Push(mL);

        //Call the function
        if (lua_pcall(mL, args.size(), 1, 0) != 0)
            std::cout << "Error calling: " + function + " " + lua_tostring(mL, -1) << std::endl;
    }

private:
    //Private members
    void Close();
    void AddLoader(int (*loader)(lua_State*));

private:
    lua_State *mL;
    std::string mFile;

public: 
    //Perform a stack dump on a state
    static int stackDump(lua_State *l);
    //Read the type value of the metatable of some udata at index i
    //Return the typename
    static std::string readType(lua_State *l, int i);

private:
    //Stuff to interface with Lua, hidden from C++
    //Functions for require modules and scripts
    static int requireModule(lua_State *l);
    static int requireScript(lua_State *l);
    static int doScript(lua_State *l);
    //The map of module loaders type and its creator
    typedef std::map<std::string, int(*)(lua_State*)> TRegisterMap;
    static TRegisterMap CreateMap();
    //The script map for lookups
    typedef std::map<std::string, LuaCScript*> TCScriptMap;
    //Script Lookup function
    static LuaCScript* GetScript(const std::string &name);
    //Map of various type adders to register proper metatables
    typedef std::map<std::string, void (*)(lua_State*, int)> TAdderMap;
    //Make the table adder map
    static TAdderMap createAdderMap();

    //For calling functions on some lua script
    static int callFunction(lua_State *caller);
    /**
    *  Check for udata being passed between states and set its metatable accordingly
    *  l: Check it's type in this state
    *  return a vector of the udata typenames, to be then used in setting up
    *  the tables in the receiving state once the params have been transferred
    */
    static std::vector<std::string> checkUdata(lua_State *l);
    /**
    *  Register the udata params with the appropriate metatables
    *  l: the state to register in
    *  udata: the type names of the udata in order
    */
    static void setUdata(lua_State *l, std::vector<std::string> udata);
    //The Lua C functions
    static const struct luaL_reg LuaCScriptLib_f[];
    //The Lua C member functions
    static const struct luaL_reg LuaCScriptLib_m[];
    //The registration function
    static int luaopen_luacscript(lua_State *l);
    //Some other necesary member functions
    static LuaCScript** checkLuaCScript(lua_State *l, int i = 1);
    //Add the appropriate metatable to a LuaCScript at index i in state l
    static void addLuaCScript(lua_State *l, int i);
    static int getScript(lua_State *l);
    //Push script name
    static int name(lua_State *l);
    //Push script bool value of open
    static int open(lua_State *l);

private:
    static const TRegisterMap sRegisterFuncs;
    static const TAdderMap sTableAdders;
    static TCScriptMap sScriptMap;
};

#endif