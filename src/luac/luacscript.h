#ifndef LUACSCRIPT_H
#define LUACSCRIPT_H

#include <map>
#include <vector>
#include <string>
#include <lua.hpp>

///A namespace for storing the Lua C API code
/**
*  A namespace to store the various functions for interacting with
*  Lua via the Lua C API
*/
namespace LuaC {
    ///The LuaScriptLib global table name (classname)
    static const std::string luaScriptClass = "LuaScript";
    /**
    *  Class to store the various functions needed for interactions
    *  between Lua and LuaScript class along with some general Lua C
    *  utility functions
    */
    class LuaScriptLib {
    public:
        /**
        *  Perform a stack dump on the lua_State
        *  @param l The lua_State to perform the stack dump on
        *  @param toFile If the stack dump should be written to Debug Log or console
        *       default is Log
        *  @return Number of return values for lua to pick up
        */
        static int StackDump(lua_State *l, bool toLog = true);
        /**
        *  Read the type value of the metatable of some userdata at index
        *  @param l The lua_State to read from
        *  @param i The index of the userdata to get the type of
        *  @return The userdata type value, as a string
        */
        static std::string readType(lua_State *l, int i);
        /**
        *  A function for looking up our engine libraries and loading them
        *  to a lua_State
        *  @param l The lua_State to load the library into
        *  @return Number of return values for lua to pick up
        */
        static int requireLib(lua_State *l);
        /**
        *  A function for looking up engine scripts and loading them to
        *  to a lua_State. An engine script is scripts/scriptname, the path
        *  will be redirected to the proper location to load from
        *  @param l The lua_State to load the script to
        *  @return Number of return values for lua to pick up
        */
        static int requireScript(lua_State *l);
        /**
        *  Copy some number of entries from the sender stack to the reciever stack
        *  The function will attempt to restore metatables, but the Lua libs must already
        *  be registered in each state for it to be able to properly register
        *  numVals data will be copied from the sender to reciever and the stack ordering
        *  will be preserved, ie. start copying at the bottom most entry in sender and push onto
        *  reciever so the stack will be identical
        *  @param sender The Lua state to transfer data from
        *  @param reciever The Lua state to transfer too
        *  @param numVals The number of entries to copy over
        */
        static void CopyStack(lua_State *sender, lua_State *reciever, int numVals);
        /**
        *  Type check some data in sender stack at index idx and copy it to the top of 
        *  the reciever stack
        *  @param sender The Lua state to copy from
        *  @param idx The index of the data to copy
        *  @param reciever The Lua state to copy too
        */
        static void CopyData(lua_State *sender, int idx, lua_State *reciever);
        /**
        *  Copy some userdata using one of the UdataCopier functions, Log issue if 
        *  a copier lookup failed
        *  @param sender The Lua state to copy from
        *  @param idx The index of the data to copy
        *  @param reciever The Lua state to copy too
        */
        static void CopyUdata(lua_State *sender, int idx, lua_State *reciever);
        /**
        *  A generic luaopen_X function for opening libraries that share similar
        *  style, and have the same organization for their luaopen_X function
        *  @param l The Lua state to register in
        *  @param metatable The name for the metatable
        *  @param className The name for the class table and type
        *  @param lib The luaL_reg struct containing the functions and names
        *  @param call The function to load for the __call field (constructor)
        */
        static int LuaOpenLib(lua_State *l, const std::string &metatable,
            const std::string &className, const luaL_reg *lib, int (*call)(lua_State*));
        /**
        *  A generic addX function for adding some userdata to the desired metatable
        *  @param l The Lua state
        *  @param i The index of the user data, relative to top
        *  @param metatable The metatable name to register with
        */
        static void Add(lua_State *l, int i, const std::string &metatable);

    private:
        /**
        *  This function is used by requireScript to actually load
        *  the script requested. doScript is pushed onto the stack by
        *  requireScript and is given the modified file path
        *  @param l The lua_State to load the script to
        *  @return Number of return values for lua to pick up
        */
        static int doScript(lua_State *l);
        ///Typedef for a map of library loader functions identified by the libname
        typedef std::map<std::string, int(*)(lua_State*)> TLuaLibs;
        /**
        *  Create the map of library loaders
        *  @return A map of the various luaopen_X functions
        */
        static TLuaLibs CreateLibMap();
        ///Typedef for a map of userdata copiers
        typedef std::map<std::string, void (*)(lua_State*, int, lua_State*)> TUdataCopiers;
        /**
        *  Create the map of the various userdata copier functions
        *  @return a map of the various copier functions
        */
        static TUdataCopiers CreateCopierMap();

    private:
        ///The Lua function library
        static const luaL_reg luaScriptLib[];
        ///Open the library
        static int luaopen_luascript(lua_State *l);
        ///Perform a stack dump to inspect some Lua data
        static int stackDump(lua_State *l);

    private:
        ///The map of library loaders
        static const TLuaLibs sLuaLibs;
        static const TUdataCopiers sUdataCopiers;
    };
}

#endif