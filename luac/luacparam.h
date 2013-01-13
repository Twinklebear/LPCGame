#ifndef LUAPARAM_H
#define LUAPARAM_H

#include <string>
#include <lua.hpp>

///A namespace for storing the Lua C API code
/**
*  A namespace to store the various functions for interacting with
*  Lua via the Lua C API
*/
namespace LuaC {
    /**
    * A class for packing together an object and the
    * appropriate function for pushing it onto the Lua state into a
    * convenient tuple so we can easily do variadic templates for calling
    * from C++ -> Lua with desired arguments 
    * We use the child classes LuaUdataParam and LuaPrimitiveParam to actually set it
    * and use this is an abstract base class
    */
    class LuaParam {
    public:
        /**
        * Push the parameter value on to a Lua state using the pusher function
        * @param l The Lua state to push the object onto
        */
        virtual void Push(lua_State *l);
        /**
        * Push the parameter onto a Lua state as a global variable with some name
        * @param l Lua state to push onto
        * @param name Global name to be given to the object
        */
        virtual void Push(lua_State *l, std::string name);
    };
}
#endif