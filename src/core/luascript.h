#ifndef LUASCRIPT_H
#define LUASCRIPT_H

#include <string>
#include <map>
#include <lua.hpp>
#include "external/json/json.h"
#include "debug.h"
#include "luac/luacfunctioninterface.h"

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
    * Store a reference to a global variable with some name
    * the reference will be stored in the reference map with
    * the same name passed in
    * @param name The name of the global to reference
    */
    void Reference(std::string name);
    /**
    * Store a reference to a the value of a field in a table
    * if the table is already in the reference system it'll be pushed
    * on and the field gotten from there
    * @param table The name of the table to get the field from
    * @param field The name of the field to reference
    */
    void Reference(std::string table, std::string field);
    /**
    * Get the LuaRef stored with some name
    * @param name The name of the reference to get
    */
    LuaC::LuaRef GetReference(std::string name);
    /**
    *  Get the lua_State pointer to use for calling functions/etc.
    *  @return The lua_State pointer held by the LuaScript class
    */
    lua_State* Get();
    ///Get the script filename
    std::string File() const;
    ///Get the name we're expecting for the object defined in the script (file - .lua)
    std::string TableName() const;
    ///Check if there's a script open
    bool Open() const;
    /**
    * Get a pointer to the function interface to call a function
    * @return Pointer to the scripts' function interface
    */
    LuaC::FunctionInterface* FunctionInterface();

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
    ///The function interface
    LuaC::FunctionInterface mFcnInterface;
    ///The map of LuaReferences
    std::map<std::string, LuaC::LuaRef> mReferences;
};

#endif