#ifndef LUACTEXT_H
#define LUACTEXT_H

#include <string>
#include <memory>
#include <lua.hpp>
#include "luacudata.h"
#include "src/text.h"

///A namespace for storing the Lua C API code
/**
*  A namespace to store the various functions for interacting with
*  Lua via the Lua C API
*/
namespace LuaC {
    ///The Text metatable name
    const std::string textMeta = "LPC.Text";
    ///the Text class/type name
    const std::string textClass = "Text";
    ///Define Text specialization for UdataLib
    template<>
    const std::string UdataLib<std::shared_ptr<Text>>::mMetaTable = textMeta;
    /**
    * The Lua library for the Text class
    */
    class TextLib : public UdataLib<std::shared_ptr<Text>> {
    public:
        ///Open the Text library in Lua state l
        static int luaopen_text(lua_State *l);

    private:
        ///The Lua function library
        static const struct luaL_reg luaTextLib[];
        ///Make a new Text in Lua state l
        static int newText(lua_State *l);
        ///Setup the text
        static int set(lua_State *l);
        ///The __newindex accessor, used for setting message, font, fontsize and color
        static int newIndex(lua_State *l);
        ///Various setters for use by newIndex
        static int setMessage(lua_State *l);
        static int setFont(lua_State *l);
        static int setSize(lua_State *l);
        static int setColor(lua_State *l);
        ///Getters
        static int getMessage(lua_State *l);
        static int getFont(lua_State *l);
        static int getFontSize(lua_State *l);
        static int getColor(lua_State *l);
        ///Get the size (w & h) of the text
        static int size(lua_State *l);
        ///Explicitly release the shared ptr
        static int release(lua_State *l);
        ///Release the shared ptr at garbage collection
        static int garbageCollection(lua_State *l);
    };
}
#endif