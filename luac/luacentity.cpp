#include <memory>
#include <lua.hpp>
#include "src/entity.h"
#include "src/physics.h"
#include "src/rect.h"
#include "src/entitymanager.h"
#include "src/statemanager.h"
#include "src/state.h"
#include "src/entitymanager.h"
#include "src/debug.h"
#include "luacscript.h"
#include "luacrectf.h"
#include "luacvector2f.h"
#include "luacphysics.h"
#include "luacentity.h"

int LuaC::EntityLib::luaopen_entity(lua_State *l){
    return LuaScriptLib::LuaOpenLib(l, entityMeta, entityClass, luaEntityLib, newEntity);
}
const struct luaL_reg LuaC::EntityLib::luaEntityLib[] = {
    { "callFunction", callFunction },
    { "destroy", destroy },
    { "release", release },
    { "physics", getPhysics },
    { "box", getBox },
    { "tag", getTag },
    { "name", getName },
    { "__newindex", newIndex },
    { "__tostring", toString },
    { "__concat", concat },
    { "__gc", garbageCollection },
    { NULL, NULL }
};
int LuaC::EntityLib::newEntity(lua_State *l){
    //Stack: class table, entity file
    std::string file = luaL_checkstring(l, 2);
    //Make a new Entity and register it with the manager
    std::shared_ptr<Entity> e = std::make_shared<Entity>(file);
    e->Init();
    //Register the Entity with the State
    std::shared_ptr<EntityManager> manager = StateManager::GetActiveState()->Manager();
    manager->Register(e);
    //Push the entity into the state
    Push(&e, l);
    return 1;
}
int LuaC::EntityLib::callFunction(lua_State *caller){
    /*
    *  Caller stack:
    *  udata             - The Entity udata we want to call the function on
    *  string (fcn name) - The function we want to call
    *  int (# results)   - # of results to return
    *  params            - All remaining values on the stack are the params to pass
    */
    //Get the lua_State of the Entity we want to call the function on
    std::shared_ptr<Entity> *e = Check(caller, 1);
    lua_State *reciever = (*e)->Script()->Get();
    //Get function name and # results
    std::string fcnName = luaL_checkstring(caller, 2);
    int nRes = luaL_checkint(caller, 3);
    LuaScriptLib::StackDump(caller);
    //# params = caller stack size - 3 (the bottom 3 are the entity, fncname and nRes)
    int nParam = lua_gettop(caller) - 3;

    //Get the function in reciever
    lua_getglobal(reciever, fcnName.c_str());
    //Reciever stack: function
    //Copy params over
    LuaScriptLib::CopyStack(caller, reciever, nParam);
    //Caller stack: params
    //Reciever stack: params
    //Call the function
    if (lua_pcall(reciever, nParam, nRes, 0) != 0){
        Debug::Log("Error calling: " + fcnName + " " + lua_tostring(reciever, -1));
        return 0;
    }
    //Reciever stack: results
    //Copy the results back
    LuaScriptLib::CopyStack(reciever, caller, nRes);
    /*
    *  Final stacks:
    *  Caller: params, results
    *  Reciever: results
    */
    return nRes;
}
int LuaC::EntityLib::destroy(lua_State *l){
    //Stack: udata (Entity) to be removed
    std::shared_ptr<Entity> *e = Check(l, 1);
    if (e != nullptr){
        std::cout << "Will try to destroy entity: " << (*e)->Name() << std::endl;
        //Remove it from the manager
        std::shared_ptr<EntityManager> manager = StateManager::GetActiveState()->Manager();
        manager->Remove(*e);
        //Come up with better way to find entity in the manager?
        e->~shared_ptr();
    }
    else
        Debug::Log("EntityLib::destroy Error: Could not lock entity. Is it already destroyed?");
    return 0;
}
int LuaC::EntityLib::release(lua_State *l){
    std::shared_ptr<Entity> *e = Check(l, 1);
    e->~shared_ptr();
    return 0;
}
int LuaC::EntityLib::getPhysics(lua_State *l){
    //Stack: udata (Entity)
    std::shared_ptr<Entity> *e = Check(l, 1);
    PhysicsLib::Push(&(*e)->GetPhysicsWeakPtr(), l);
    return 1;
}
int LuaC::EntityLib::getBox(lua_State *l){
    //Stack: udata (Entity)
    std::shared_ptr<Entity> *e = Check(l, 1);
    RectfLib::Push(&(*e)->Box(), l);
    return 1;
}
int LuaC::EntityLib::getTag(lua_State *l){
    //Stack: udata (Entity)
    std::shared_ptr<Entity> *e = Check(l, 1);
    lua_pushstring(l, (*e)->Tag().c_str());
    return 1;
}
int LuaC::EntityLib::getName(lua_State *l){
    //Stack: udata (Entity)
    std::shared_ptr<Entity> *e = Check(l, 1);
    lua_pushstring(l, (*e)->Name().c_str());
    return 1;
}
int LuaC::EntityLib::newIndex(lua_State *l){
    //Stack: udata (Entity), string of index to set, val to set as
    std::string index = luaL_checkstring(l, 2);
    switch(index.at(0)){
        case 't':
            return setTag(l, 3);
        default:
            break;
    }
    return 0;
}
int LuaC::EntityLib::setTag(lua_State *l, int i){
    //Stack: udata, ??? with tag @ i
    std::shared_ptr<Entity> *e = Check(l, 1);
    std::string tag = luaL_checkstring(l, i);
    (*e)->SetTag(tag);
    return 0;
}
int LuaC::EntityLib::toString(lua_State *l){
    return 1;
}
int LuaC::EntityLib::concat(lua_State *l){
    return 1;
}
int LuaC::EntityLib::garbageCollection(lua_State *l){
    std::shared_ptr<Entity> *e = Check(l, 1);
    e->~shared_ptr();
    return 0;
}
