#ifndef DEBUG_H
#define DEBUG_H

#include <fstream>
#include <string>
#include <luabind/luabind.hpp>

/**
*  A simple debug logging class, will write strings to debug.log
*  in the same folder as exe
*/
class Debug {
public:
    ///Initialize the debug log
    static void Init();
    ///Close the debug log
    static void Quit();
    /**
    *  Write some string to the debug log
    *  The text will be given a timestamp and written out,
    *  Time is measured since program initializiation in HH:MM:SS
    *  @param text The text to log
    */
    static void Log(const std::string text);
    /**
	*  Register the Debug class with the lua state
	*  @param l The lua_State to register the module with
	*/
	static int RegisterLua(lua_State *l);

private:
    static std::ofstream logOut;
};

#endif