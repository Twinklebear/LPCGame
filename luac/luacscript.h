#ifndef LUACSCRIPT
#define LUACSCRIPT

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
        *  @return Number of return values for lua to pick up
        */
        static int stackDump(lua_State *l);
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
        *  Check for userdata in state l and return a vector of the types
        *  of the userdata
        *  @param l The state to read the userdata types from
        *  @return Vector containing the userdata typenames in the order they
                were encountered
        */
        static std::vector<std::string> checkUserData(lua_State *l);
        /**
        *  Set the userdata types with the appropriate metatables based off 
        *  a vector of the typenames, the vector indices correspond to the
        *  order the userdata is in. Ie. @1 = 1st userdata, @2 = 2nd userdata
        *  @param l The lua_State to set the tables in
        *  @param types The vector to read typenames from
        */
        static void setUserData(lua_State *l, std::vector<std::string> types);

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
        ///Typedef for a map of metatable adder functions, for giving the desired table to some userdata
        typedef std::map<std::string, void (*)(lua_State*, int)> TTableAdders;
        /**
        *  Create the map of various metatable adder functions
        *  @return A map of the various table adder functions
        */
        static TTableAdders CreateAdderMap();

    private:
        ///The map of library loaders
        static const TLuaLibs sLuaLibs;
        static const TTableAdders sTableAdders;
    };
};

#endif