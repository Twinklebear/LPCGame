#ifndef LUAPARAM_H
#define LUAPARAM_H

#include <lua.hpp>

/**
* LuaParam is a class for packing together an object and the
* appropriate function for pushing it onto the Lua state into a
* convenient tuple so we can easily do variadic templates for calling
* from C++ -> Lua with desired arguments
*/
template<class T>
class LuaParam {
public:
    LuaParam(T* obj, void (*push)(lua_State*, T*)){
    }
};

#endif