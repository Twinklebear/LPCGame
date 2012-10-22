#include <memory>
#include <lua.hpp>
#include "src/entity.h"
#include "src/physics.h"
#include "src/rect.h"
#include "src/entitymanager.h"
#include "luac/luacentity.h"

const std::string LuaC::EntityLib::sMetaTable = "LPC.Entity";
const std::string LuaC::EntityLib::sClassName = "Entity";

int LuaC::EntityLib::luaopen_entity(lua_State *l){
    //Stack: lib name
    //Push the metatable to contain the fcns onto the stack
    luaL_newmetatable(l, sMetaTable.c_str());
    //Copy metatable from -1 to the top
    lua_pushvalue(l, -1);
    //Set table at -2 key of __index = top of stack
    //ie. LPC.LuaRect.__index = table containing luaRectLib_m
    lua_setfield(l, -2, "__index");
    //Register the lib to the metatable at top of stack
    luaL_register(l, NULL, luaEntityLib);
    //Stack: lib name, metatable
    //Add type identifier to the metatable
    lua_pushstring(l, sClassName.c_str());
    lua_setfield(l, -2, "type");
    //Stack: lib name, metatable
    //Setup the LuaRect table, for making LuaRects
    lua_newtable(l);
    //Stack: lib name, metatable, table
    //Push the new fcn
    lua_pushcfunction(l, newEntity);
    //Stack: lib name, metatable, table, newLuaRect fcn
    //Now newLuaRect fcn is @ key __call in the table
    lua_setfield(l, -2, "__call");
    //Stack: lib name, metatable, table
    //We want to set the table containing __call to be the metatable
    //of the LuaRect metatable
    lua_setmetatable(l, -2);
    //Stack: lib name, metatable
    //Name our metatable and make it global
    lua_setglobal(l, sClassName.c_str());
    //Stack: lib name
    return 0;
}
void LuaC::EntityLib::addEntity(lua_State *l, int i){
    //Given stack containing unknown amount of things along with the udata
    //udata is at index i
    luaL_getmetatable(l, sMetaTable.c_str());
    //Now stack is ??? with the metatable at top
    //So we know the index of our rect is bumped down 1 more so we adjust
    //and set the table
    lua_setmetatable(l, i - 1);
}
Entity** LuaC::EntityLib::checkEntity(lua_State *l, int i){
    return (Entity**)luaL_checkudata(l, i, sMetaTable.c_str());
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
    std::string val = luaL_checkstring(l, 2);
    switch(val.at(0)){
        case 't':
            setTag(l, 3);
            break;
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
