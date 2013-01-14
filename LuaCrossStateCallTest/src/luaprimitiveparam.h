#ifndef LUAPRIMITIVEPARAM_H
#define LUAPRIMITIVEPARAM_H

#include <functional>
#include <string>
#include <lua.hpp>

///A namespace for storing the Lua C API code
/**
* A namespace to store the various functions for interacting with
* Lua via the Lua C API
*/
namespace LuaC {
    class LuaParam {
    public:
        virtual void Push(lua_State *l) = 0;
        virtual void Push(lua_State *l, std::string name) = 0;
    };

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
        * Retrieve a result from the top of the stack of Lua state
        * ie. a return value from the called function
        */
        static T Retrieve(lua_State *l){
            return mRetriever(l, -1);
        }

    private:
        const T mObj;
        const static std::function<void(lua_State*, T)> mPusher;
        const static std::function<T(lua_State*, int)> mRetriever;
    };
    //Pusher function specializations
    //Bool
    typedef LuaPrimitiveParam<bool> BoolParam;
    const std::function<void(lua_State*, bool)> BoolParam::mPusher = lua_pushboolean;
    const std::function<bool(lua_State*, int)>
        BoolParam::mRetriever = [](lua_State *l, int idx) { return lua_toboolean(l, idx) == 1; };
    //Double
    typedef LuaPrimitiveParam<double> DoubleParam;
    const std::function<void(lua_State*, double)> DoubleParam::mPusher = lua_pushnumber;
    const std::function<double(lua_State*, int)> DoubleParam::mRetriever = luaL_checknumber;
    //Float
    typedef LuaPrimitiveParam<float> FloatParam;
    const std::function<void(lua_State*, float)> FloatParam::mPusher = lua_pushnumber;
    const std::function<float(lua_State*, int)> FloatParam::mRetriever = luaL_checknumber;
    //Int
    typedef LuaPrimitiveParam<int> IntParam;
    const std::function<void(lua_State*, int)> IntParam::mPusher = lua_pushinteger;
    const std::function<int(lua_State*, int)> IntParam::mRetriever = luaL_checkinteger;
    //String (a lambda function is used b/c lua_pushstring takes a char* not a std::string)
    typedef LuaPrimitiveParam<std::string> StringParam;
    const std::function<void(lua_State*, std::string)>
        StringParam::mPusher = [](lua_State *l, std::string str){ lua_pushstring(l, str.c_str()); };
    //const std::function<std::string(lua_State*, int)>
        //StringParam::mRetriever = luaL_checkstring;
    /*
    //For void return type something else needs to be done
    typedef LuaPrimitiveParam<void> VoidParam;
    const std::function<void(lua_State*, int)>
        VoidParam::mRetriever = [](lua_State *l, int idx){ return; };
    */
}
#endif