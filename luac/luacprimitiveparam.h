#ifndef LUAPRIMITIVEPARAM_H
#define LUAPRIMITIVEPARAM_H

#include <functional>
#include <string>
#include <lua.hpp>

///A namespace for storing the Lua C API code
/**
*  A namespace to store the various functions for interacting with
*  Lua via the Lua C API
*/
namespace LuaC {
    template<class T>
    class LuaPrimitiveParam : public LuaParam {
    public:
        /**
        * Construct the parameter, giving it the value it will be pushing onto the state
        * @param obj The object to be pushed into the state
        */
        LuaPrimitiveParam(T obj) : mObj(obj) {}
        /**
        * Push the parameter value on to a Lua state using the pusher function
        * @param l The Lua state to push the object onto
        */
        void Push(lua_State *l) override {
            mPusher(l, mObj);
        }
        /**
        * Push the parameter onto a Lua state as a global variable with some name
        * @param l Lua state to push onto
        * @param name Global name to be given to the object
        */
        void Push(lua_State *l, std::string name) override {
            Push(l);
            lua_setglobal(l, name.c_str());
        }

    private:
        const T mObj;
        const static std::function<void(lua_State*, T)> mPusher;
    };
    template<>
    const std::function<void(lua_State*, int)> LuaPrimitiveParam<int>::mPusher = lua_pushinteger;
}
#endif