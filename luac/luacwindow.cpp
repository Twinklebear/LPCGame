#include <string>
#include <lua.hpp>
#include "src/debug.h"
#include "src/image.h"
#include "src/animatedimage.h"
#include "src/text.h"
#include "src/window.h"
#include "luacscript.h"
#include "luacimage.h"
#include "luacrectf.h"
#include "luacvector2f.h"
#include "luacwindow.h"

int LuaC::WindowLib::luaopen_window(lua_State *l){
    //Stack: lib name
    //Register the library as global table "Window"
    luaL_register(l, windowClass.c_str(), luaWindowLib);
    return 0;
}
///The Lua function library
const struct luaL_reg LuaC::WindowLib::luaWindowLib[] = {
    { "draw", draw },
    { "box", getBox },
    { NULL, NULL }
};
int LuaC::WindowLib::draw(lua_State *l){
    /*
    *  Multiple possible stacks, the 3 we check here are:
    *  1. Image, other params
    *  2. AnimatedImage, other params
    *  3. Text, other params
    */
    std::string type = LuaScriptLib::readType(l, 1);
    //Case 1
    if (type.at(0) == 'I')
        DrawImage(l);
    else if (type.at(0) == 'A')
        DrawAnimatedImage(l);
    else if (type.at(0) == 'T')
        DrawText(l);
    else
        Debug::Log("WindowLib:draw Error: " + type + " is not drawable");
    return 0;
}
int LuaC::WindowLib::getBox(lua_State *l){
    Rectf r = Window::Box();
    RectfLib::PushRectf(&r, l);
    return 1;
}
///The functions called when resolving draw parameters
void LuaC::WindowLib::DrawImage(lua_State *l){
    /**
    *  3 Possible stacks:
    *  1. Image, Rectf destination
    *  2. Image, Rectf destination, Rectf clip
    *  3. Image, Rectf destination, Rectf clip, float rotation,
    *     Vector2f pivot, int flip value
    */
    std::shared_ptr<Image> *img = ImageLib::checkImage(l, 1);
    //Case 1:
    if (lua_gettop(l) == 2){
        Rectf *dst = RectfLib::checkRectf(l, 2);
        Window::Draw(img->get(), *dst);
    }
    //Case 2:
    else if (lua_gettop(l) == 3){
        Rectf *dst = RectfLib::checkRectf(l, 2);
        Rectf *clipf = RectfLib::checkRectf(l, 3);
        Recti clip = *clipf;
        Window::Draw(img->get(), *dst, &clip);
    }

}
void LuaC::WindowLib::DrawAnimatedImage(lua_State *l){

}
void LuaC::WindowLib::DrawText(lua_State *l){

}
