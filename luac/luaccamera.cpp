#include <string>
#include <memory>
#include <lua.hpp>
#include "src/debug.h"
#include "src/camera.h"
#include "luacscript.h"
#include "luacentity.h"
#include "luacrectf.h"
#include "luacvector2f.h"
#include "luaccamera.h"

int LuaC::CameraLib::luaopen_camera(lua_State *l){
    //We use a custom registration function b/c the Camera shouldn't have
    //an exposed constructor
    //Stack: lib name
    //Push the metatable to contain fcns onto the stack
    luaL_newmetatable(l, cameraMeta.c_str());
    //Copy metatable from -1 to top
    lua_pushvalue(l, -1);
    //Set table at -2 key of __index = top of stack,
    //ie. LPC.Camera.__index = table at top, ie. itself
    lua_setfield(l, -2, "__index");
    //Register the functions
    luaL_register(l, NULL, luaCameraLib);
    //Stack: lib name, metatable
    //Add the type field
    lua_pushstring(l, cameraClass.c_str());
    lua_setfield(l, -2, "type");
    //Stack: lib name, metatable
    return 1;
}
void LuaC::CameraLib::addCamera(lua_State *l, int i){
    LuaScriptLib::Add(l, i, cameraMeta.c_str());
}
std::weak_ptr<Camera>* LuaC::CameraLib::checkCamera(lua_State *l, int i){
    return (std::weak_ptr<Camera>*)luaL_checkudata(l, i, cameraMeta.c_str());
}
void LuaC::CameraLib::PushCamera(std::weak_ptr<Camera> *camera, lua_State *l){
    std::weak_ptr<Camera> *c = AllocateCamera(l);
    *c = *camera;
}
void LuaC::CameraLib::CopyCamera(lua_State *from, int idx, lua_State *too){
    std::weak_ptr<Camera> *c = checkCamera(from, idx);
    PushCamera(c, too);
}
std::weak_ptr<Camera>* LuaC::CameraLib::AllocateCamera(lua_State *l){
    void *block = lua_newuserdata(l, sizeof(std::weak_ptr<Camera>));
    std::weak_ptr<Camera> *c = new(block) std::weak_ptr<Camera>();
    addCamera(l, -1);
    return c;
}
const struct luaL_reg LuaC::CameraLib::luaCameraLib[] = {
    { "setFocus", setFocus },
    { "inCamera", inCamera },
    { "offset", offset },
    { "centering", centering },
    { NULL, NULL }
};
int LuaC::CameraLib::setFocus(lua_State *l){
    //Stack: camera, entity
    std::weak_ptr<Camera> *weak = checkCamera(l, 1);
    std::shared_ptr<Entity> *e = EntityLib::checkEntity(l, 2);
    if (!weak->expired()){
        auto c = weak->lock();
        c->SetFocus(*e);
    }
    else
        Debug::Log("CameraLib:setFocus error: Camera expired");
    return 0;
}
int LuaC::CameraLib::inCamera(lua_State *l){
    //Stack: camera, rectf
    std::weak_ptr<Camera> *weak = checkCamera(l, 1);
    Rectf *r = RectfLib::Check(l, 2);
    bool inCam = false;
    if (!weak->expired()){
        auto c = weak->lock();
        inCam = c->InCamera(*r);
    }
    else 
        Debug::Log("CameraLib:inCamera error: Camera expired");

    lua_pushboolean(l, inCam);
    return 1;
}
int LuaC::CameraLib::offset(lua_State *l){
    //Stack: camera
    std::weak_ptr<Camera> *weak = checkCamera(l, 1);
    Vector2f vect(0, 0);
    if (!weak->expired()){
        auto c = weak->lock();
        vect = c->Offset();
    }
    else
        Debug::Log("CameraLib:offset error: Camera expired");
    
    Vector2f *v = Vector2fLib::Allocate(l);
    *v = vect;
    return 1;
}
int LuaC::CameraLib::centering(lua_State *l){
    //Stack: camera
    std::weak_ptr<Camera> *weak = checkCamera(l, 1);
    Vector2f vect(0, 0);
    if (!weak->expired()){
        auto c = weak->lock();
        vect = c->Centering();
    }
    else
        Debug::Log("CameraLib:offset error: Camera expired");
    
    Vector2f *v = Vector2fLib::Allocate(l);
    *v = vect;
    return 1;
}