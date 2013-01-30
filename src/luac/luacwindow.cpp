#include <string>
#include <SDL.h>
#include <lua.hpp>
#include "core/debug.h"
#include "core/image.h"
#include "core/animatedimage.h"
#include "core/text.h"
#include "core/window.h"
#include "luacscript.h"
#include "luacimage.h"
#include "luacanimatedimage.h"
#include "luactext.h"
#include "luacrectf.h"
#include "luacvector2f.h"
#include "luacwindow.h"

int LuaC::WindowLib::luaopen_window(lua_State *l){
    //Stack: lib name
    //Register the library as global table "Window"
    luaL_register(l, windowClass.c_str(), luaWindowLib);
    openFlipEnum(l);
    return 0;
}
void LuaC::WindowLib::openFlipEnum(lua_State *l){
    //Stack: lib name, table
    lua_pushinteger(l, SDL_FLIP_NONE);
    lua_setfield(l, -2, "FLIP_NONE");
    lua_pushinteger(l, SDL_FLIP_HORIZONTAL);
    lua_setfield(l, -2, "FLIP_HORIZONTAL");
    lua_pushinteger(l, SDL_FLIP_VERTICAL);
    lua_setfield(l, -2, "FLIP_VERTICAL");
}
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
    //Case 2
    else if (type.at(0) == 'A')
        DrawAnimatedImage(l);
    //Case 3
    else if (type.at(0) == 'T')
        DrawText(l);
    else
        Debug::Log("WindowLib:draw Error: " + type + " is not drawable");

    return 0;
}
int LuaC::WindowLib::getBox(lua_State *l){
    Rectf r = Window::Box();
    RectfLib::Push(l, &r);
    return 1;
}
void LuaC::WindowLib::DrawImage(lua_State *l){
    /**
    * 3 Possible stacks:
    * 1. Image, Rectf destination
    * 2. Image, Rectf destination, Rectf clip
    * 3. Image, Rectf destination, Rectf clip, float rotation,
    *     Vector2f pivot, int flip value
    */
    std::shared_ptr<Image> *img = ImageLib::Check(l, 1);
    //Case 1:
    if (lua_gettop(l) == 2){
        Rectf *dst = RectfLib::Check(l, 2);
        Window::Draw(img->get(), *dst);
    }
    //Case 2:
    else if (lua_gettop(l) == 3){
        Rectf *dst = RectfLib::Check(l, 2);
        Rectf *clipf = RectfLib::Check(l, 3);
        Recti clip = *clipf;
        Window::Draw(img->get(), *dst, &clip);
    }
    else if (lua_gettop(l) == 6){
        Rectf *dst = RectfLib::Check(l, 2);
        Rectf *clipf = RectfLib::Check(l, 3);
        Recti clip = *clipf;
        float angle = luaL_checknumber(l, 4);
        Vector2f *pivot = Vector2fLib::Check(l, 5);
        int flip = luaL_checkint(l, 6);
        Window::Draw(img->get(), *dst, &clip, angle, *pivot, flip);
    }
    else
        Debug::Log("Window.draw(Image, ...) invalid number of parameters: \nstack:" + LuaScriptLib::StackDump(l));
}
void LuaC::WindowLib::DrawAnimatedImage(lua_State *l){
    /**
    * 2 Possible stacks:
    * 1. AnimatedImage, Rectf destination
    * 2. AnimatedImage, Rectf destination, float rotation, Vector2f pivot,
    *       int flip value
    */
    std::shared_ptr<AnimatedImage> *img = AnimatedImageLib::Check(l, 1);
    //Case 1:
    if (lua_gettop(l) == 2){
        Rectf *dst = RectfLib::Check(l, 2);
        Window::Draw(img->get(), *dst);
    }
    //Case 2:
    else if (lua_gettop(l) == 5){
        Rectf *dst = RectfLib::Check(l, 2);
        float angle = luaL_checknumber(l, 3);
        Vector2f *pivot = Vector2fLib::Check(l, 4);
        int flip = luaL_checknumber(l, 5);
        Window::Draw(img->get(), *dst, angle, *pivot, flip);
    }
    else
        Debug::Log("Window.draw(AnimatedImage, ...) invalid number of parameters: \nstack:" + LuaScriptLib::StackDump(l));
}
void LuaC::WindowLib::DrawText(lua_State *l){
    /**
    * 2 Possible stacks:
    * 1. Text, Rectf destination
    * 2. Text, Rectf destination, float rotation, Vector2f pivot, int flip value
    */
    std::shared_ptr<Text> *txt = TextLib::Check(l, 1);
    //Case 1:
    if (lua_gettop(l) == 2){
        Rectf *dst = RectfLib::Check(l, 2);
        Window::Draw(txt->get(), *dst);
    }
    //Case 2:
    else if (lua_gettop(l) == 5){
        Rectf *dst = RectfLib::Check(l, 2);
        float angle = luaL_checknumber(l, 3);
        Vector2f *pivot = Vector2fLib::Check(l, 4);
        int flip = luaL_checknumber(l, 5);
        Window::Draw(txt->get(), *dst, angle, *pivot, flip);
    }
    else
        Debug::Log("Window.draw(Text, ...) invalid number of parameters: \nstack:" + LuaScriptLib::StackDump(l));
}
