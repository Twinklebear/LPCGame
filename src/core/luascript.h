#ifndef LUASCRIPT_H
#define LUASCRIPT_H

#include <string>
#include <map>
#include <vector>
#include <lua.hpp>
#include "external/json/json.h"
#include "debug.h"
#include "luac/luacparam.h"

///A class to enable lua scripts to load various modules
/**
*  ModuleManager enables Lua scripts to import other necessary modules
*/
class LuaScript {
public:
    LuaScript();
    /**
    *  Create the LuaScript instance and open a script
    *  @param script The script to open
    */
    LuaScript(std::string script);
    ~LuaScript();
    /**
    *  Open the desired Lua script to be run as the entity's behavior script
    *  @param script The script file to open
    */
    void OpenScript(const std::string &script);
    ///Close the script
    void Close();
    /**
    *  Get the lua_State pointer to use for calling functions/etc.
    *  @return The lua_State pointer held by the LuaScript class
    */
    lua_State* Get();
    ///Get the script filename
    std::string File() const;
    ///Check if there's a script open
    bool Open() const;
    /**
    * Call a function on the Lua state and pass some arguments to it
    * @param function Name of the function to be called
    * @param args Vector of arguments to be passed
    */
    template<class ReturnType>
    auto CallFunction(std::string function, 
        std::vector<LuaC::LuaParam*> args = std::vector<LuaC::LuaParam*>()) -> decltype(ReturnType::Retrieve(mL))
    {
        //Get the function to be called
        lua_getglobal(mL, function.c_str());
        //Push params onto stack
        for (LuaC::LuaParam *p : args)
            p->Push(mL);

        //Call the function
        if (lua_pcall(mL, args.size(), 1, 0) != 0)
            Debug::Log("Error calling: " + function + " in script: " + mFile + " " + lua_tostring(mL, -1));

        return ReturnType::Retrieve(mL);
    }
    //For calling a function with no return values
    void CallFunction(std::string function, std::vector<LuaC::LuaParam*> args = std::vector<LuaC::LuaParam*>()){
        //Get the function to be called
        lua_getglobal(mL, function.c_str());
        //Push params onto stack
        for (LuaC::LuaParam *p : args)
            p->Push(mL);

        //Call the function
        if (lua_pcall(mL, args.size(), 0, 0) != 0)
            Debug::Log("Error calling: " + function + " in script: " + mFile + " " + lua_tostring(mL, -1));
    }

private:
    /**
    *  Add a loader function to the package.loaders table
    *  @param loader The lua_cfunction to add
    */
    void AddLoader(int (*loader)(lua_State*));
    
private:
    ///The lua state running the script
    lua_State *mL;
    ///The script file name
    std::string mFile;
    ///Tracking if the script is open
    bool mOpen;
};

#endif