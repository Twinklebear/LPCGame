#ifndef LUACCAMERA_H
#define LUACCAMERA_H

#include <string>
#include <memory>
#include <lua.hpp>
#include "luacudata.h"
#include "src/camera.h"

///A namespace for storing the Lua C API code
/**
*  A namespace to store the various functions for interacting with
*  Lua via the Lua C API
*/
namespace LuaC {
    ///The Camera metatable name
    const std::string cameraMeta = "LPC.Camera";
    ///The Camera class/type name
    const std::string cameraClass = "Camera";
    ///Define template specialization for Camera
    template<>
    const std::string UdataLib<std::weak_ptr<Camera>>::mMetaTable = cameraMeta;
    /**
    *  The Lua library for the Camera class
    */
    class CameraLib : public UdataLib<std::weak_ptr<Camera>> {
    public:
        ///Open the Camera library for Lua state l
        static int luaopen_camera(lua_State *l);

    private:
        ///The Lua function library
        static const struct luaL_reg luaCameraLib[];
        /**
        *  The exposed functions, names are same as the C++ function they call, see
        *  their comments for a description of the function action
        */
        static int setFocus(lua_State *l);
        //static int update(lua_State *l);
        static int inCamera(lua_State *l);
        //TODO: Add these later, but are they even needed?
        //static int move(lua_State *l);
        //static int pan(lua_State *l);
        //static int scene(lua_State *l);
        //static int getBox(lua_State *l);
        //static int setBox(lua_State *l);
        //static int getSceneBox(lua_State *l);
        //static int setSceneBox(lua_State *l);
        static int offset(lua_State *l);
        static int centering(lua_State *l);
    };
}

#endif