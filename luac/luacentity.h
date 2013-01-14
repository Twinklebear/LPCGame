#ifndef LUACENTITY_H
#define LUACENTITY_H

#include <string>
#include <memory>
#include <lua.hpp>
#include "luacudata.h"
#include "src/entity.h"

///A namespace for storing the Lua C API code
/**
*  A namespace to store the various functions for interacting with
*  Lua via the Lua C API
*/
namespace LuaC {
    ///The Entity metatable name
    const std::string entityMeta = "LPC.Entity";
    ///The Entity class/type name
    const std::string entityClass = "Entity";
    ///Define Entity specialization for UdataLib
    template<>
    const std::string UdataLib<std::shared_ptr<Entity>>::mMetaTable = entityMeta;
    /**
    *  Class for storing functions used to manage interaction
    *  between Lua and the Entity class. Defines the Entity Lua Lib
    */
    class EntityLib : public UdataLib<std::shared_ptr<Entity>> {
    public:
        ///Open the Entity Lua library for Lua state l
        static int luaopen_entity(lua_State *l);
        /**
        * Check if the weak pointer is expired, if yes spit out debug log and return nullptr
        * if not expired return weak_ptr
        * @param weak The weak_ptr to check
        * @param function The function name to show in the debug log
        * @return shared_ptr if the ptr hasn't expired, nullptr if it has
        */
        static std::shared_ptr<Entity> GetShared(std::weak_ptr<Entity> weak, std::string function);

    private:
        ///The Lua function library struct
        static const struct luaL_reg luaEntityLib[];
        ///Make a new Entity in Lua state l
        static int newEntity(lua_State *l);
        ///Call a function on the Entity's script
        static int callFunction(lua_State *caller);
        //Destroy the Entity, removing it from the manager and existence
        static int destroy(lua_State *l);
        //Release the Entity shared ptr
        static int release(lua_State *l);
        ///Getters
        static int getPhysics(lua_State *l);
        static int getBox(lua_State *l);
        static int getTag(lua_State *l);
        static int getName(lua_State *l);
        ///__newindex accessor for setters
        static int newIndex(lua_State *l);
        ///Setters
        ///Set the entity tag, i corresponds to the index to get the value from
        static int setTag(lua_State *l, int i);
        ///Operators
        static int toString(lua_State *l);
        static int concat(lua_State *l);
        ///Garbage collection
        static int garbageCollection(lua_State *l);
    };
}

#endif