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
        /**
        * Get the Lua Param from the top of the Lua Stack
        * Used for retrieving the return value of a Lua function call
        * @param l Lua state to get result from
        */
        static T Retrieve(lua_State *l) {
            return mRetriever(l, -1);
        }

    private:
        const T mObj;
        const static std::function<void(lua_State*, T)> mPusher;
        const static std::function<T(lua_State*, int)> mRetriever;
    };
    //Bool
    typedef LuaPrimitiveParam<bool> BoolParam;
    template<>
    const std::function<void(lua_State*, bool)> BoolParam::mPusher = lua_pushboolean;
    //We need to use this in-between lambda for now due to compiler issues
    const static auto bRetrieve = [](lua_State *l, int idx){ return lua_toboolean(l, idx) == 1; };
    template<>
    const std::function<bool(lua_State*, int)> BoolParam::mRetriever = bRetrieve;

    //Double
    typedef LuaPrimitiveParam<double> DoubleParam;
    template<>
    const std::function<void(lua_State*, double)> DoubleParam::mPusher = lua_pushnumber;
    template<>
    const std::function<double(lua_State*, int)> DoubleParam::mRetriever = luaL_checknumber;
    
    //Float
    typedef LuaPrimitiveParam<float> FloatParam;
    template<>
    const std::function<void(lua_State*, float)> FloatParam::mPusher = lua_pushnumber;
    template<>
    const std::function<float(lua_State*, int)> FloatParam::mRetriever = luaL_checknumber;
    
    //Int
    typedef LuaPrimitiveParam<int> IntParam;
    template<>
    const std::function<void(lua_State*, int)> IntParam::mPusher = lua_pushinteger;
    template<>
    const std::function<int(lua_State*, int)> IntParam::mRetriever = luaL_checkinteger;
    
    //String (a lambda function is used b/c lua_pushstring takes a char* not a std::string)
    typedef LuaPrimitiveParam<std::string> StringParam;
    //We need to use this in-between lambda for now due to compiler issues
    const static auto sPusher = [](lua_State *l, std::string str){ return lua_pushstring(l, str.c_str()); };
    template<>
    const std::function<void(lua_State*, std::string)>  StringParam::mPusher = sPusher;
    //We need to use this in-between lambda for now due to compiler issues
    const static auto sRetriever = [](lua_State *l, int i){ return (std::string)luaL_checkstring(l, i); };
    template<>
    const std::function<std::string(lua_State*, int)> StringParam::mRetriever = sRetriever;

}
#endif