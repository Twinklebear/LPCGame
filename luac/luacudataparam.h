#ifndef LUAUDATAPARAM_H
#define LUAUDATAPARAM_H

#include <functional>
#include <string>
#include <lua.hpp>
#include "luacparam.h"
#include "luacvector2f.h"

///A namespace for storing the Lua C API code
/**
*  A namespace to store the various functions for interacting with
*  Lua via the Lua C API
*/
namespace LuaC {
    /**
    * A class for packing together one of our classes and its Lua lib Push function
    * so that we can easily push it onto a Lua state and use it as a parameter
    */
    template<class T>
    class LuaUdataParam : public LuaParam {
    public:
        /**
        * Construct the parameter, giving it a pointer to the object it's pushing
        * @param obj The object to be pushed into the state
        */
        LuaUdataParam(T* obj) : mObj(obj) {}
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
        const T *mObj;
        const static std::function<void(lua_State*, const T*)> mPusher;
    };
    template<>
    const std::function<void(lua_State*, const Vector2f*)> LuaUdataParam<Vector2f>::mPusher = &Vector2fLib::Push;
}
#endif