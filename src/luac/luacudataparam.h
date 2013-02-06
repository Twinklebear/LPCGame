#ifndef LUAUDATAPARAM_H
#define LUAUDATAPARAM_H

#include <functional>
#include <string>
#include <memory>
#include <lua.hpp>
#include "luacudata.h"
#include "luacparam.h"
#include "luacvector2f.h"
#include "luacrectf.h"
#include "luacphysics.h"
#include "luacentity.h"
#include "luacdebug.h"
#include "luaccolor.h"
#include "luactimer.h"
#include "luacinput.h"
#include "luacstate.h"
#include "luaccamera.h"
#include "luacmath.h"
#include "luacimage.h"
#include "luacwindow.h"
#include "luacanimatedimage.h"
#include "luactext.h"

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
        LuaUdataParam(T obj) : mObj(obj) {}
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
        //Debug function only, get the param stored
        const T DebugGet(){
            return mObj;
        }

    private:
        const T mObj;
        const static std::function<void(lua_State*, const T)> mPusher;
        const static std::function<T(lua_State*, int)> mRetriever;
    };
    //We use UdataLib's Push/Check functions for each type so get the appropriate instance
    template<class T>
    const std::function<void(lua_State*, const T)>
        LuaUdataParam<T>::mPusher = &UdataLib<T>::Push;
    template<class T>
    const std::function<T(lua_State*, int)>
        LuaUdataParam<T>::mRetriever = &UdataLib<T>::Check;

    //Shorthand typedefs
    typedef LuaUdataParam<std::shared_ptr<AnimatedImage>> AnimImgParam;
    typedef LuaUdataParam<std::weak_ptr<Camera>> CameraParam;
    typedef LuaUdataParam<Color> ColorParam;
    typedef LuaUdataParam<std::shared_ptr<Entity>> EntityParam;
    typedef LuaUdataParam<std::shared_ptr<Image>> ImageParam;
    typedef LuaUdataParam<std::weak_ptr<Physics>> PhysicsParam;
    typedef LuaUdataParam<Rectf> RectfParam;
    typedef LuaUdataParam<std::shared_ptr<Text>> TextParam;
    typedef LuaUdataParam<Timer> TimerParam;
    typedef LuaUdataParam<Vector2f> Vector2fParam;
}
#endif