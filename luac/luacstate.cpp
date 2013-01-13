#include <string>
#include <lua.hpp>
#include "src/statemanager.h"
#include "src/state.h"
#include "src/debug.h"
#include "luacentity.h"
#include "luacstate.h"

int LuaC::StateLib::luaopen_state(lua_State *l){
    //Stack: lib name
    //Register the library as global table "State"
    luaL_register(l, stateClass.c_str(), luaStateLib);
    //Stack: lib name, table
    return 0;
}
const luaL_reg LuaC::StateLib::luaStateLib[] = {
    { "getEntity", getEntity },
    { "changeScene", setExit },
    { "name", getName },
    { NULL, NULL }
};
int LuaC::StateLib::getEntity(lua_State *l){
    //Stack: entity name
    std::string name = luaL_checkstring(l, 1);
    //Get the active state's entitymanager and try to lookup the entity
    std::shared_ptr<EntityManager> manager = StateManager::GetActiveState()->Manager();
    std::shared_ptr<Entity> entity = manager->GetEntity(name);
    if (entity != nullptr)
        EntityLib::Push(l, &entity);       
    else {
        std::string err = "StateLib::getEntity: Failed to find Entity: " + name;
        Debug::Log(err);
        lua_pushnil(l);
    }        
    //Stack: entity name, userdata (Entity) or nil
    return 1;
}
int LuaC::StateLib::setExit(lua_State *l){
    //Stack: statename to change too
    std::string stateName = luaL_checkstring(l, 1);
    std::shared_ptr<State> state = StateManager::GetActiveState();
    state->SetExit(stateName);
    return 0;
}
int LuaC::StateLib::getName(lua_State *l){
    //Stack: empty
    std::shared_ptr<State> state = StateManager::GetActiveState();
    lua_pushstring(l, state->Name().c_str());
    return 1;
}