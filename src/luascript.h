#ifndef LUASCRIPT_H
#define LUASCRIPT_H

#include <string>
#include <vector>
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
	*  Load the modules that the script needs from the list of modules needed mModules
	*/
	void LoadModules();
	/**
	*  Load the desired module, passed as a MODULE enum
	*  @param module The module to load
	*/
	void LoadModule(int module);
    /**
    *  Function to export to package.preload to allow for loading modules
    *  via require
    *  @param l The lua_State to register the module with
    *  @param module The module name to load
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

public:
	///An enum for easily selecting the desired module to load
	enum MODULE { ANIMATED_IMAGE, BUTTON, CAMERA, COLOR, ENTITY, IMAGE, INPUT, MATH, MOTION_STATE, 
				  PHYSICS, RECT, STATE, STATE_MANAGER, TEXT, TIMER, VECTOR, WINDOW };

private:
	///The lua state running the script
	lua_State *mL;
	///The script file name
	std::string mFile;
	///The modules the script needs
	std::vector<int> mModules;
};

#endif