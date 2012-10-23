#include <memory>
#include <lua.hpp>
#include "src/entity.h"
#include "src/physics.h"
#include "src/rect.h"
#include "src/entitymanager.h"
#include "luacscript.h"
#include "luacrectf.h"
#include "luacvector2f.h"
#include "luacphysics.h"
#include "luacentity.h"

const std::string LuaC::EntityLib::sMetatable = "LPC.Entity";
const std::string LuaC::EntityLib::sClassName = "Entity";

int LuaC::EntityLib::luaopen_entity(lua_State *l){
    return LuaScriptLib::LuaOpenLib(l, sMetatable, sClassName, luaEntityLib, newEntity);
}
void LuaC::EntityLib::addEntity(lua_State *l, int i){
    LuaScriptLib::Add(l, i, sMetatable);
}
Entity** LuaC::EntityLib::checkEntity(lua_State *l, int i){
    return (Entity**)luaL_checkudata(l, i, sMetatable.c_str());
}
const struct luaL_reg LuaC::EntityLib::luaEntityLib[] = {
    { "physics", getPhysics },
    { "box", getBox },
    { "tag", getTag },
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
    Entity *e = new Entity(file);
    std::shared_ptr<Entity> sObj(e);
    //Need to lookup active state via statemanager and register the entity

    //Make the userdata
    Entity **luaE = (Entity**)lua_newuserdata(l, sizeof(Entity*));
    *luaE = sObj.get();
    addEntity(l, -1);
    return 1;
}
int LuaC::EntityLib::getPhysics(lua_State *l){
    //Stack: udata (Entity)
    Entity **e = checkEntity(l, 1);
    //Make a new Physics userdata
    Physics** luaP = (Physics**)lua_newuserdata(l, sizeof(Physics*));
    //Give it the Physics metatable
    PhysicsLib::addPhysics(l, -1);
    //Set it to the entity's physics
    *luaP = (*e)->GetPhysics();
    return 1;
}
int LuaC::EntityLib::getBox(lua_State *l){
    //Stack: udata (Entity)
    Entity **e = checkEntity(l, 1);
    //Make a new Rectf
    Rectf *r = (Rectf*)lua_newuserdata(l, sizeof(Rectf));
    //Give it the Rectf metatable
    RectfLib::addRectf(l, -1);
    //Is this correct?
    *r = (*e)->Box();
    return 1;
}
int LuaC::EntityLib::getTag(lua_State *l){
    //Stack: udata (Entity)
    Entity **e = checkEntity(l, 1);
    lua_pushstring(l, (*e)->Tag().c_str());
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
    Entity **e = checkEntity(l, 1);
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
    return 0;
}
