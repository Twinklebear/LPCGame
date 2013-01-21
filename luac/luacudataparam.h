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
        /**
        * Get the Lua Param from the top of the Lua Stack
        * Used for retrieving the return value of a Lua function call
        * @param l Lua state to get result from
        */
        static T* Retrieve(lua_State *l) {
            return mRetriever(l, -1);
        }

    private:
        const T *mObj;
        const static std::function<void(lua_State*, const T*)> mPusher;
        const static std::function<T*(lua_State*, int)> mRetriever;
    };
    //Is there a way i can enable doing this? I'd need to somehow deduce the lib
    //from the type T
    /*
    template<class T>
    const std::function<void(lua_State*, const T*)>
        LuaUdataParam<T>::mPusher = &T::Push;
    template<class T>
    const std::function<T*(lua_State*, int)>
        LuaUdataParam<T>::mRetriever = &T::Check;
        */
    //Pusher function specializations & shorthand typedefs
    //Animated Image
    typedef LuaUdataParam<std::shared_ptr<AnimatedImage>> AnimImgParam;
    template<>
    const std::function<void(lua_State*, const std::shared_ptr<AnimatedImage>*)> 
        AnimImgParam::mPusher = &AnimatedImageLib::Push;
    template<>
    const std::function<std::shared_ptr<AnimatedImage>*(lua_State*, int)>
        AnimImgParam::mRetriever = &AnimatedImageLib::Check;

    //Camera
    typedef LuaUdataParam<std::weak_ptr<Camera>> CameraParam;
    template<>
    const std::function<void(lua_State*, const std::weak_ptr<Camera>*)> 
        CameraParam::mPusher = &CameraLib::Push;
    template<>
    const std::function<std::weak_ptr<Camera>*(lua_State*, int)>
        CameraParam::mRetriever = &CameraLib::Check;
        
    //Color
    typedef LuaUdataParam<Color> ColorParam;
    template<>
    const std::function<void(lua_State*, const Color*)>
        ColorParam::mPusher = &ColorLib::Push;
    template<>
    const std::function<Color*(lua_State*, int)>
        ColorParam::mRetriever = &ColorLib::Check;
        
    //Entity
    typedef LuaUdataParam<std::shared_ptr<Entity>> EntityParam;
    template<>
    const std::function<void(lua_State*, const std::shared_ptr<Entity>*)>
        EntityParam::mPusher = &EntityLib::Push;
    template<>
    const std::function<std::shared_ptr<Entity>*(lua_State*, int)>
        EntityParam::mRetriever = &EntityLib::Check;
        
    //Image
    typedef LuaUdataParam<std::shared_ptr<Image>> ImageParam;
    template<>
    const std::function<void(lua_State*, const std::shared_ptr<Image>*)>
        ImageParam::mPusher = &ImageLib::Push;
    template<>
    const std::function<std::shared_ptr<Image>*(lua_State*, int)>
        ImageParam::mRetriever = &ImageLib::Check;
        
    //Physics
    typedef LuaUdataParam<std::weak_ptr<Physics>> PhysicsParam;
    template<>
    const std::function<void(lua_State*, const std::weak_ptr<Physics>*)>
        PhysicsParam::mPusher = &PhysicsLib::Push;
    template<>
    const std::function<std::weak_ptr<Physics>*(lua_State*, int)>
        PhysicsParam::mRetriever = &PhysicsLib::Check;
        
    //Rectf
    typedef LuaUdataParam<Rectf> RectfParam;
    template<>
    const std::function<void(lua_State*, const Rectf*)>
        RectfParam::mPusher = &RectfLib::Push;
    template<>
    const std::function<Rectf*(lua_State*, int)>
        RectfParam::mRetriever = &RectfLib::Check;
        
    //Text
    typedef LuaUdataParam<std::shared_ptr<Text>> TextParam;
    template<>
    const std::function<void(lua_State*, const std::shared_ptr<Text>*)>
        TextParam::mPusher = &TextLib::Push;
    template<>
    const std::function<std::shared_ptr<Text>*(lua_State*, int)>
        TextParam::mRetriever = &TextLib::Check;
        
    //Timer
    typedef LuaUdataParam<Timer> TimerParam;
    template<>
    const std::function<void(lua_State*, const Timer*)> 
        TimerParam::mPusher = &TimerLib::Push;
    template<>
    const std::function<Timer*(lua_State*, int)>
        TimerParam::mRetriever = &TimerLib::Check;
        
    //Vector2f
    typedef LuaUdataParam<Vector2f> Vector2fParam;
    template<>
    const std::function<void(lua_State*, const Vector2f*)> 
        Vector2fParam::mPusher = &Vector2fLib::Push;
    template<>
    const std::function<Vector2f*(lua_State*, int)>
        Vector2fParam::mRetriever = &Vector2fLib::Check;
}
#endif