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
};

#endif