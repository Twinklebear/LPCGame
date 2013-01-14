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
/**
* Check if the weak pointer is expired, if yes spit out debug log and return nullptr
* if not expired return weak_ptr
* @param weak The weak_ptr to check
* @param function The function name to show in the debug log
* @return shared_ptr if the ptr hasn't expired, nullptr if it has
*/
std::shared_ptr<Entity> LuaC::EntityLib::GetShared(std::weak_ptr<Entity> weak, std::string function){
    if (weak.expired()){
        Debug::Log("Entity lib " + function + " Error: the weak pointer has expired");
        return nullptr;
    }
    else
        return weak.lock();
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
    //Register the Entity with the State
    std::shared_ptr<EntityManager> manager = StateManager::GetActiveState()->Manager();
    manager->Register(e);
    e->Init();
    //std::weak_ptr<Entity> eWeak = e;
    //Push the entity into the state
    Push(l, &e);
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
    /*
    std::weak_ptr<Entity> *eWeak = Check(caller, 1);
    std::shared_ptr<Entity> e = GetShared(*eWeak, "callFunction");
    if (e == nullptr)
        return 0;
    */
    std::shared_ptr<Entity> *e = Check(caller, 1);
    lua_State *reciever = (*e)->Script()->Get();
    //Get function name and # results
    std::string fcnName = luaL_checkstring(caller, 2);
    int nRes = luaL_checkint(caller, 3);
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
    /*
    std::weak_ptr<Entity> *eWeak = Check(l, 1);
    std::shared_ptr<Entity> e = GetShared(*eWeak, "destroy");
    if (e == nullptr)
        return 0;
    */
    std::shared_ptr<Entity> *e = Check(l, 1);
    std::cout << "Will try to destroy entity: " << (*e)->Name() << std::endl;
    //Remove it from the manager
    std::shared_ptr<EntityManager> manager = StateManager::GetActiveState()->Manager();
    //Come up with better way to find entity in the manager?
    manager->Remove(*e);

    return 0;
}
int LuaC::EntityLib::release(lua_State *l){
    std::cout << "EntityLib release" << std::endl;
    //std::weak_ptr<Entity> *e = Check(l, 1);
    //e->~weak_ptr();
    std::shared_ptr<Entity> *e = Check(l, 1);
    e->~shared_ptr();
    return 0;
}
int LuaC::EntityLib::getPhysics(lua_State *l){
    //Stack: udata (Entity)
    /*
    std::weak_ptr<Entity> *eWeak = Check(l, 1);
    std::shared_ptr<Entity> e = GetShared(*eWeak, "physics");
    if (e == nullptr)
        return 0;
    */
    std::shared_ptr<Entity> *e = Check(l, 1);
    PhysicsLib::Push(l, &(*e)->GetPhysicsWeakPtr());
    return 1;
}
int LuaC::EntityLib::getBox(lua_State *l){
    //Stack: udata (Entity)
    /*
    std::weak_ptr<Entity> *eWeak = Check(l, 1);
    std::shared_ptr<Entity> e = GetShared(*eWeak, "box");
    if (e == nullptr)
        return 0;
    */
    std::shared_ptr<Entity> *e = Check(l, 1);
    RectfLib::Push(l, &(*e)->Box());
    return 1;
}
int LuaC::EntityLib::getTag(lua_State *l){
    //Stack: udata (Entity)
    /*
    std::weak_ptr<Entity> *eWeak = Check(l, 1);
    std::shared_ptr<Entity> e = GetShared(*eWeak, "tag");
    if (e == nullptr)
        return 0;
    */
    std::shared_ptr<Entity> *e = Check(l, 1);
    lua_pushstring(l, (*e)->Tag().c_str());
    return 1;
}
int LuaC::EntityLib::getName(lua_State *l){
    //Stack: udata (Entity)
    /*
    std::weak_ptr<Entity> *eWeak = Check(l, 1);
    std::shared_ptr<Entity> e = GetShared(*eWeak, "name");
    if (e == nullptr)
        return 0;
    */
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
    /*
    std::weak_ptr<Entity> *eWeak = Check(l, 1);
    std::shared_ptr<Entity> e = GetShared(*eWeak, "set tag");
    if (e == nullptr)
        return 0;
    */
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
    release(l);
    return 0;
}
