#include <string>
#include <memory>
#include <lua.hpp>
#include "core/text.h"
#include "luacudata.h"
#include "luacscript.h"
#include "luaccolor.h"
#include "luactext.h"

int LuaC::TextLib::luaopen_text(lua_State *l){
    return LuaScriptLib::LuaOpenLib(l, textMeta, textClass, luaTextLib, newText);
}
const struct luaL_reg LuaC::TextLib::luaTextLib[] = {
    { "set", set },
    { "release", release },
    { "message", getMessage },
    { "font", getFont },
    { "fontSize", getFontSize },
    { "color", getColor },
    { "size", size },
    { "w", width },
    { "h", height },
    { "__newindex", newIndex },
    { "__gc", garbageCollection },
    { NULL, NULL }
};
int LuaC::TextLib::newText(lua_State *l){
    //Stack: class table, message, font file, color, font size
    std::string msg = luaL_checkstring(l, 2);
    std::string fontFile = luaL_checkstring(l, 3);
    Color *color = ColorLib::Check(l, 4);
    int size = luaL_checkint(l, 5);

    Push(l, &std::make_shared<Text>(msg, fontFile, *color, size));
    return 1;
}
int LuaC::TextLib::set(lua_State *l){
    //Stack: text to set values of, message, font file, color, font size
    std::shared_ptr<Text> *txt = Check(l, 1);
    std::string msg = luaL_checkstring(l, 2);
    std::string fontFile = luaL_checkstring(l, 3);
    Color *color = ColorLib::Check(l, 4);
    int size = luaL_checkint(l, 5);

    (*txt)->Set(msg, fontFile, *color, size);
    return 0;
}
int LuaC::TextLib::newIndex(lua_State *l){
    //Stack: text, string of index to set, val for index
    std::string index = luaL_checkstring(l, 2);
    switch (index.at(0)){
        case 'm':
            return setMessage(l);
        case 'f':
            return setFont(l);
        case 's':
            return setSize(l);
        case 'c':
            return setColor(l);
        default:
            return 0;
    }
}
int LuaC::TextLib::setMessage(lua_State *l){
    //Stack: text, string of index to set, message to set
    std::shared_ptr<Text> *txt = Check(l, 1);
    std::string msg = luaL_checkstring(l, 3);
    (*txt)->SetMessage(msg);
    return 0;
}
int LuaC::TextLib::setFont(lua_State *l){
    //Stack: text, string of index to set, font file to use
    std::shared_ptr<Text> *txt = Check(l, 1);
    std::string font = luaL_checkstring(l, 3);
    (*txt)->SetFont(font);
    return 0;
}
int LuaC::TextLib::setSize(lua_State *l){
    //Stack: text, string of index to set, font size to set
    std::shared_ptr<Text> *txt = Check(l, 1);
    int size = luaL_checkint(l, 3);
    (*txt)->SetFontSize(size);
    return 0;
}
int LuaC::TextLib::setColor(lua_State *l){
    //Stack: text, string of index to set, color to set
    std::shared_ptr<Text> *txt = Check(l, 1);
    Color *color = ColorLib::Check(l, 3);
    (*txt)->SetColor(*color);
    return 0;
}
int LuaC::TextLib::getMessage(lua_State *l){
    //Stack: text
    std::shared_ptr<Text> *txt = Check(l, 1);
    lua_pushstring(l, (*txt)->GetMessage().c_str());
    return 1;
}
int LuaC::TextLib::getFont(lua_State *l){
    //Stack: text
    std::shared_ptr<Text> *txt = Check(l, 1);
    lua_pushstring(l, (*txt)->GetFont().c_str());
    return 1;
}
int LuaC::TextLib::getFontSize(lua_State *l){
    //Stack: text
    std::shared_ptr<Text> *txt = Check(l, 1);
    lua_pushinteger(l, (*txt)->GetFontSize());
    return 1;
}
int LuaC::TextLib::getColor(lua_State *l){
    //Stack: text
    std::shared_ptr<Text> *txt = Check(l, 1);
    ColorLib::Push(l, &(*txt)->GetColor());
    return 1;
}
int LuaC::TextLib::size(lua_State *l){
    //Stack: text
    std::shared_ptr<Text> *txt = Check(l, 1);
    lua_pushinteger(l, (*txt)->W());
    lua_pushinteger(l, (*txt)->H());
    return 2;
}
int LuaC::TextLib::width(lua_State *l){
    //Stack: text
    std::shared_ptr<Text> *txt = Check(l, 1);
    lua_pushinteger(l, (*txt)->W());
    return 1;
}
int LuaC::TextLib::height(lua_State *l){
    //Stack: text
    std::shared_ptr<Text> *txt = Check(l, 1);
    lua_pushinteger(l, (*txt)->H());
    return 1;
}
int LuaC::TextLib::release(lua_State *l){
    //Stack: text
    std::shared_ptr<Text> *txt = Check(l, 1);
    txt->~shared_ptr();
    return 0;
}
int LuaC::TextLib::garbageCollection(lua_State *l){
    return release(l);
}
