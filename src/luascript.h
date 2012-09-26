#ifndef LUASCRIPT_H
#define LUASCRIPT_H

#include <string>
#include <vector>
#include <unordered_map>
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
    *  Gets the module loading function from the TRegisterLuaMap of functions
    *  and runs it, passing it l
    *  @param l The lua_State to register the module with
    *  @param module The module name to load
    *  @return T if the module was found and loaded, F otherwise
    */
    static bool RequireModule(lua_State *l, std::string module);
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
	*  Register the LuaScript module loader function with the
	*  lua state member
	*/
	void RegisterLua();

private:
    ///typedef for an unordered map of the RegisterLua functions
    typedef std::unordered_map<std::string, void (*)(lua_State*)> TRegisterLuaMap;
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
    static const TRegisterLuaMap mRegisterLuaFuncs;
};

#endif