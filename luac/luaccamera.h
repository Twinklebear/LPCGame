#ifndef LUACCAMERA_H
#define LUACCAMERA_H

#include <string>
#include <memory>
#include <lua.hpp>
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
    /**
    *  The Lua library for the Camera class
    */
    class CameraLib {
    public:
        ///Open the Camera library for Lua state l
        static int luaopen_camera(lua_State *l);
        /**
        *  Add the Camera metatable to the userdata at index i
        *  i is relative to top (ie. -1 is top)
        *  @param l The Lua state
        *  @param i The index of the userdata to add (index relative to top, neg #'s)
        */
        static void addCamera(lua_State *l, int i);
        /**
        *  Check if the userdata at index i in the stack is a Camera
        *  and return a pointer to it
        *  @param l The Lua state
        *  @param i The index of the userdata (standard index, pos #'s)
        */
        static std::weak_ptr<Camera>* checkCamera(lua_State *l, int i);
        /**
        *  Push a Camera onto the stack of some Lua state
        *  @param camera The Camera to push onto the stack
        *  @param l The Lua State to push onto
        */
        static void PushCamera(std::weak_ptr<Camera> *camera, lua_State *l);
        /**
        *  Copy a Camera at some index in one Lua state's stack
        *  to the top of some other state's stack
        *  @param from The Lua state to copy the Camera from
        *  @param idx The index in the stack of from of the Physics
        *  @param too The Lua state to copy the Camera into
        */
        static void CopyCamera(lua_State *from, int idx, lua_State *too);
        /**
        *  Allocate memory for a Camera on some lua_State and assign it the 
        *  Physics metatable
        *  @param l The Lua state to allocate memory on
        *  @return Pointer to the allocated Camera
        */
        static std::weak_ptr<Camera>* AllocateCamera(lua_State *l);

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