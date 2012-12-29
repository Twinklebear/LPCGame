#ifndef LUACIMAGE_H
#define LUACIMAGE_H

#include <string>
#include <memory>
#include <lua.hpp>
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
    /**
    *  Class for storing functions for interacting with Image objects
    *  from Lua. Defines the Image Lua Lib
    */
    class ImageLib {
    public:
        //Open the Image Lua library for Lua state l
        static int luaopen_image(lua_State *l);
        /**
        *  Add the Image metatable to the userdata at index i
        *  i is relative to top (ie. -1 is top)
        *  @param l The Lua state
        *  @param i The index of userdata to add (index relative to top, neg #'s)
        */
        static void addImage(lua_State *l, int i);
        /**
        *  Check if the userdata at index i in the stack is an Image
        *  and return a pointer to it
        *  @param l The Lua state
        *  @param i The index of the userdata (standard index, pos #'s)
        */
        static std::shared_ptr<Image>* checkImage(lua_State *l, int i);
        /**
        *  Push a Image onto the stack of some Lua state
        *  @param image The Image to push onto the stack
        *  @param l The Lua State to push onto
        */
        static void PushImage(std::shared_ptr<Image> *image, lua_State *l);
        /**
        *  Copy an Image at some index in one Lua state's stack
        *  to the top of some other state's stack
        *  @param from The Lua state to copy the Image from
        *  @param idx The index in the stack of from of the Image
        *  @param too The Lua state to copy the Image into
        */
        static void CopyImage(lua_State *from, int idx, lua_State *too);
        /**
        *  Allocate memory for an Image on some lua_State and assign it the 
        *  Image metatable
        *  @param l The Lua state to allocate memory on
        *  @return Pointer to the allocated Image
        */
        static std::shared_ptr<Image>* AllocateImage(lua_State *l);

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
        ///Get the image filename
        static int file(lua_State *l);
        ///Explicitly release the shared pointer
        static int release(lua_State *l);
        ///Release the shared pointer at garbage collection
        static int garbageCollection(lua_State *l);
    };
}

#endif