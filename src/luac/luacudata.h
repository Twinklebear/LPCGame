#ifndef LUACUDATA_H
#define LUACUDATA_H

#include <string>
#include <lua.hpp>
#include "luacscript.h"

///A namespace for storing the Lua C API code
/**
*  A namespace to store the various functions for interacting with
*  Lua via the Lua C API
*/
namespace LuaC {
    /**
    *  A base template class for inherting methods for performing udata
    *  memory operations on Lua states
    */
    template<class T>
    class UdataLib {
    public:
        /**
        *  Allocate memory for an instance of T in the Lua state, initialize it, 
        *  assign the appropriate metatable and return a pointer to the object
        *  @param l The Lua state to make the object in
        *  @return pointer to the allocated object
        */
        static T* Allocate(lua_State *l){
            void *block = lua_newuserdata(l, sizeof(T));
            T *obj = new(block) T();
            AddMetaTable(l, -1);
            return obj;
        }
        /**
        *  Push a copy of an object of type T onto the stack of the Lua state
        *  @param obj The object to push
        *  @param l The Lua state to push onto
        */
        static void Push(lua_State *l, const T obj){
            T *o = Allocate(l);
            *o = obj;
        }
        /**
        *  Copy an object of type T from one Lua state at index i to another Lua state
        *  @param from The Lua state to copy from
        *  @param idx The index of the data in the from stack
        *  @param too The Lua state to copy too
        */
        static void Copy(lua_State *from, int idx, lua_State *too){
            T* obj = Check(from, idx);
            Push(too, *obj);
        }
        /**
        *  Check if the userdata at some index is of type T and return it if it is
        *  @param l The Lua state
        *  @param i The index of the userdata
        */
        static T* Check(lua_State *l, int i){
            return (T*)luaL_checkudata(l, i, mMetaTable.c_str());
        }

    private:
        /**
        *  Add the metatable for the type to the userdata at index i relative to top
        *  @param l The Lua state the data is in
        *  @param i The index of the userdata to register, idx relative to top (negative #'s)
        */
        static void AddMetaTable(lua_State *l, int i){
            LuaScriptLib::Add(l, i, mMetaTable);
        }

    private:
        ///The metatable name, value is set via template specialization for the desired class
        static const std::string mMetaTable;
    };
    template<class T>
    const std::string UdataLib<T>::mMetaTable = "";

    ////Specialization for primitive types
    //typedef UdataLib<int> IntLib;
    //template<>
    //static void IntLib::Push(lua_State *l, const int obj){
    //    lua_pushinteger(l, obj);
    //}
    //template<>
    //static void IntLib::Copy(lua_State *from, int idx, lua_State *too){
    //    int val = luaL_checkint(from, idx);
    //    lua_pushinteger(too, val);
    //}
    //template<>
    //static int& IntLib::Check(lua_State *l, int i){
    //    return luaL_checkint(l, i);
    //}
}

#endif