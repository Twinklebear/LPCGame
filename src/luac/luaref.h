#ifndef LUAREF_H
#define LUAREF_H

#include <string>
#include <memory>
#include <lua.hpp>
#include "luacdata.h"

///A namespace for storing the Lua C API code
/**
*  A namespace to store the various functions for interacting with
*  Lua via the Lua C API
*/
namespace LuaC {
    //Tracks a Lua reference
    /**
    * A handler for a Lua reference, can be constructed to reference
    * some item on the stack or a global with some name
    * also inherits from LuaParam so that it may be treated as a regular
    * parameter when calling Lua functions
    */
    class LuaRef {
    public:
        /**
        * Blank constructor, the reference will be set to null (LUA_REFNIL)
        */
        LuaRef();
        /**
        * Store a reference to the item at index i in the stack of lua_State l
        * @param l The state that the item exists in
        * @param i The stack index of the item to be referenced
        */
        LuaRef(lua_State *l, int i);
        /**
        * Store a reference to a global of some name in lua_State l
        * @param l The state the item exists in
        * @param name The name of the global to be referenced
        */
        LuaRef(lua_State *l, std::string name);
        //Unref the the item
        ~LuaRef();
        /**
        * Push the reference onto the stack of its Lua state. A check is performed
        * to make sure that the state being pushed onto is the same as the one being 
        * passed, to make sure you're doing what you think you're doing. This is because 
        * references can only be used in the state they were created
        * @param l The Lua state we want the object to be pushed in, checked against
        *   the state the reference exists in
        */
        void Push(lua_State *l) const;
        /**
        * Push the reference onto the stack of its Lua state. A check is performed
        * to make sure that the state being pushed onto is the same as the one being 
        * passed, to make sure you're doing what you think you're doing. This is because 
        * references can only be used in the state they were created
        * @param l The Lua state we want the object to be pushed in, checked against
        *   the state the reference exists in
        * @param name The global name to be assigned to the variable
        */
        void Push(lua_State *l, std::string name) const;

    private:
        //The reference number
        //int mRef;
        /**
        * The reference number, we use a shared_ptr to track how many
        * things are referencing the item so we don't free it early
        */
        std::shared_ptr<int> mRef;
        ///The state the reference is in
        lua_State *mState;
    };
}

#endif