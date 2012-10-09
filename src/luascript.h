#ifndef LUASCRIPT_H
#define LUASCRIPT_H

#include <string>
#include <map>
#include <luabind/luabind.hpp>
#include "../externals/json/json.h"

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
	void OpenScript(std::string script);
	/**
	*  Get the lua_State pointer to use for calling functions/etc.
	*  @return The lua_State pointer held by the LuaScript class
	*/
	lua_State* Get();
	///Get the script filename
	std::string File();
	///Check if there's a script open
	bool Open();
	/**
	*  Load the LuaScript filename and desired module list from a Json::Value
	*  @param v The Json::Value to load from
	*/
	void Load(Json::Value v);
	/**
	*  Save the LuaScript filename and module list to a Json::Value & return it
	*  @return The Json::Value containing the LuaScript configuration
	*/
	Json::Value Save();

private:
    ///Close the active script
	void Close();
    /**
    *  Gets the module loading function from mRegisterLuaFunc
    *  and pushes it onto the lua_Stack for execution
    *  @param l The lua_State to register the module with
    *  @return 1, the actual return is pushed onto the lua_State's stack
    */
    static int RequireModule(lua_State *l);
    /**
    *  If a game script is attempting to be loaded, ie name of script
    *  is scripts/* we attempt to call dofile on a script of that
    *  name in the res/scripts directory
    *  @param l The lua_State to load the script too
    *  @return 1
    */
    static int RequireScript(lua_State *l);
    /**
    *  The function pushed onto the Lua stack by RequireScript
    *  Gets the modified script filepath and calls dofile on it
    */
    static int DoScript(lua_State *l);
    /**
    *  Get ahold of the package.loaders table from lua_State mL and 
    *  add the RequireModule function to it. This is done via 
    *  the Lua C API, I'm unsure if I can do this with Luabind, 
    *  probably can but I don't know how
    */
    void AddModuleLoader();
    /**
    *  Get ahold of the package.loaders table from lua_State mL and 
    *  add the RequireScript function to it
    *  Done the same way as AddModuleLoader
    */
    void AddScriptLoader();
    ///Add both loaders to the lua_State
    void AddLoaders();

private:
    ///typedef for an unordered map of the RegisterLua functions
    typedef std::map<std::string, int (*)(lua_State*)> TRegisterLuaMap;
    /**
    *  Create the unordered_map of RegisterLua functions and return it
    *  @return unordered_map of RegisterLua functions
    */
    static TRegisterLuaMap CreateMap();

private:
	///The lua state running the script
	lua_State *mL;
	///The script file name
	std::string mFile;
    ///The map of RegisterLua functions
    static const TRegisterLuaMap mRegisterLuaFunc;
};

#endif