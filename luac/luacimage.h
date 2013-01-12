#ifndef LUACIMAGE_H
#define LUACIMAGE_H

#include <string>
#include <memory>
#include <lua.hpp>
#include "luacudata.h"
#include "src/image.h"

///A namespace for storing the Lua C API code
/**
*  A namespace to store the various functions for interacting with
*  Lua via the Lua C API
*/
namespace LuaC {
    //The Image metatable name
    const std::string imageMeta = "LPC.Image";
    //The Image class/type name
    const std::string imageClass = "Image";
    ///Define Image specialization for UdataLib
    template<>
    const std::string UdataLib<std::shared_ptr<Image>>::mMetaTable = imageMeta;
    /**
    *  Class for storing functions for interacting with Image objects
    *  from Lua. Defines the Image Lua Lib
    */
    class ImageLib : public UdataLib<std::shared_ptr<Image>> {
    public:
        //Open the Image Lua library for Lua state l
        static int luaopen_image(lua_State *l);

    private:
        ///The Lua function library struct
        static const struct luaL_reg luaImageLib[];
        ///Make a new Image in Lua state l
        static int newImage(lua_State *l);
        ///Get the Rectf of some clip, if no index passed will return the active clip
        static int getClip(lua_State *l);
        ///Set the active clip
        static int setActiveClip(lua_State *l);
        ///Get the total number of clips 
        static int clipCount(lua_State *l);
        ///Get the size of the image
        static int size(lua_State *l);
        ///Get the image width
        static int width(lua_State *l);
        ///Get the imag height
        static int height(lua_State *l);
        ///Get the image filename
        static int file(lua_State *l);
        ///Explicitly release the shared pointer
        static int release(lua_State *l);
        ///Release the shared pointer at garbage collection
        static int garbageCollection(lua_State *l);
    };
}

#endif