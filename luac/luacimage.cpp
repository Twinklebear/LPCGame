#include <string>
#include <memory>
#include <lua.hpp>
#include "src/image.h"
#include "luacscript.h"
#include "luacrectf.h"
#include "luacimage.h"

int LuaC::ImageLib::luaopen_image(lua_State *l){
    return LuaScriptLib::LuaOpenLib(l, imageMeta, imageClass, luaImageLib, newImage);
}
void LuaC::ImageLib::addImage(lua_State *l, int i){
    LuaScriptLib::Add(l, i, imageMeta);
}
std::shared_ptr<Image>* LuaC::ImageLib::checkImage(lua_State *l, int i){
    return (std::shared_ptr<Image>*)luaL_checkudata(l, i, imageMeta.c_str());
}
void LuaC::ImageLib::PushImage(std::shared_ptr<Image> *image, lua_State *l){
    std::shared_ptr<Image>* img = AllocateImage(l);
    *img = *image;
}
void LuaC::ImageLib::CopyImage(lua_State *from, int idx, lua_State *too){
    std::shared_ptr<Image> *img = checkImage(from, idx);
    PushImage(img, too);
}
std::shared_ptr<Image>* LuaC::ImageLib::AllocateImage(lua_State *l){
    void *block = lua_newuserdata(l, sizeof(std::shared_ptr<Image>));
    std::shared_ptr<Image> *img = new(block) std::shared_ptr<Image>();
    addImage(l, -1);
    return img;
}
const struct luaL_reg LuaC::ImageLib::luaImageLib[] = {
    { "clip", getClip },
    { "setActiveClip", setActiveClip },
    { "clipCount", clipCount },
    { "size", size },
    { "file", file },
    { "release", release },
    { "__gc", garbageCollection },
    { NULL, NULL }
};
int LuaC::ImageLib::newImage(lua_State *l){
    //Stack: class table, file name
    std::string file = luaL_checkstring(l, 2);
    //Make a new Image in the state
    std::shared_ptr<Image> *img = AllocateImage(l);
    *img = std::make_shared<Image>(file);
    return 1;
}
int LuaC::ImageLib::getClip(lua_State *l){
    /*
    *  Two possible stacks: 
    *  1. image userdata, index of the clip to get
    *  2. image userdata. clip desired is the active clip
    */
    std::shared_ptr<Image> *img = checkImage(l, 1);
    Rectf clip;
    //Case 1:
    if (lua_isnumber(l, 2)){
        int idx = luaL_checkint(l, 2);
        clip = (*img)->Clip(idx);
    }
    //Case 2:
    else
        clip = (*img)->Clip();

    RectfLib::Push(&clip, l);
    return 1;
}
int LuaC::ImageLib::setActiveClip(lua_State *l){
    //Stack: image (udata), clip to set active
    std::shared_ptr<Image> *img = checkImage(l, 1);
    int clipNum = luaL_checkint(l, 2);
    (*img)->SetActiveClip(clipNum);
    return 0;
}
int LuaC::ImageLib::clipCount(lua_State *l){
    //Stack: image (udata)
    std::shared_ptr<Image> *img = checkImage(l, 1);
    lua_pushinteger(l, (*img)->ClipCount());
    return 1;
}
int LuaC::ImageLib::size(lua_State *l){
    //Stack: image (udata)
    std::shared_ptr<Image> *img = checkImage(l, 1);
    lua_pushinteger(l, (*img)->W());
    lua_pushinteger(l, (*img)->H());
    return 2;
}
int LuaC::ImageLib::file(lua_State *l){
    //Stack: image (udata)
    std::shared_ptr<Image> *img = checkImage(l, 1);
    lua_pushstring(l, (*img)->File().c_str());
    return 1;
}
int LuaC::ImageLib::release(lua_State *l){
    std::shared_ptr<Image> *img = checkImage(l, 1);
    img->~shared_ptr();
    return 0;
}
int LuaC::ImageLib::garbageCollection(lua_State *l){
    return release(l);
}
