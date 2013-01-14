#ifndef LUAUDATAPARAM_H
#define LUAUDATAPARAM_H

#include <functional>
#include <string>
#include <memory>
#include <lua.hpp>
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
    //Pusher function specializations & shorthand typedefs
    //Animated Image
    typedef LuaUdataParam<std::shared_ptr<AnimatedImage>> AnimImgParam;
    template<>
    const std::function<void(lua_State*, const std::shared_ptr<AnimatedImage>*)> 
        LuaUdataParam<std::shared_ptr<AnimatedImage>>::mPusher = &AnimatedImageLib::Push;
    //Camera
    typedef LuaUdataParam<std::weak_ptr<Camera>> CameraParam;
    template<>
    const std::function<void(lua_State*, const std::weak_ptr<Camera>*)> 
        LuaUdataParam<std::weak_ptr<Camera>>::mPusher = &CameraLib::Push;  
    //Color
    typedef LuaUdataParam<Color> ColorParam;
    const std::function<void(lua_State*, const Color*)>
        LuaUdataParam<Color>::mPusher = &ColorLib::Push;
    //Entity
    typedef LuaUdataParam<std::weak_ptr<Entity>> EntityParam;
    const std::function<void(lua_State*, const std::weak_ptr<Entity>*)>
        LuaUdataParam<std::weak_ptr<Entity>>::mPusher = &EntityLib::Push;
    //Image
    typedef LuaUdataParam<std::shared_ptr<Image>> ImageParam;
    const std::function<void(lua_State*, const std::shared_ptr<Image>*)>
        LuaUdataParam<std::shared_ptr<Image>>::mPusher = &ImageLib::Push;
    //Physics
    typedef LuaUdataParam<std::weak_ptr<Physics>> PhysicsParam;
    const std::function<void(lua_State*, const std::weak_ptr<Physics>*)>
        LuaUdataParam<std::weak_ptr<Physics>>::mPusher = &PhysicsLib::Push;
    //Rectf
    typedef LuaUdataParam<Rectf> RectfParam;
    template<>
    const std::function<void(lua_State*, const Rectf*)> 
        LuaUdataParam<Rectf>::mPusher = &RectfLib::Push;
    //Text
    typedef LuaUdataParam<std::shared_ptr<Text>> TextParam;
    const std::function<void(lua_State*, const std::shared_ptr<Text>*)>
        LuaUdataParam<std::shared_ptr<Text>>::mPusher = &TextLib::Push;
    //Timer
    typedef LuaUdataParam<Timer> TimerParam;
    template<>
    const std::function<void(lua_State*, const Timer*)> 
        LuaUdataParam<Timer>::mPusher = &TimerLib::Push;
    //Vector2f
    typedef LuaUdataParam<Vector2f> Vector2fParam;
    template<>
    const std::function<void(lua_State*, const Vector2f*)> 
        LuaUdataParam<Vector2f>::mPusher = &Vector2fLib::Push;
}
#endif