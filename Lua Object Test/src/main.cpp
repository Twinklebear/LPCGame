#include <lua.hpp>
#include <iostream>
#include <string>
#include "luacscript.h"
#include "luaprimitiveparam.h"
#include "luaref.h"

int main(int argc, char** argv){
    //The two scripts we'll be using to test this
    LuaCScript sA("../res/scripts/scriptA.lua");

    //Get the raw state to mess with
    lua_State *l = sA.Get();
    /*lua_getglobal(l, "entity");
    LuaRef entityRef(l, 1);*/
    LuaRef entityRef(l, "entity");
    entityRef.Push();
    //Push on a new field entry
    lua_pushstring(l, "test");
    lua_pushstring(l, "testOKEYDOKEY");
    lua_rawset(l, 1);
    std::cout << "setfield, stack: ";
    sA.stackDump(l);
    std::cout << "getting field test contains: ";
    lua_getfield(l, 1, "test");
    std::cout << lua_tostring(l, -1) << std::endl;
    std::cout << "stack post get: ";
    sA.stackDump(l);
    //pop it off
    lua_pop(l, 1);

    lua_getfield(l, 1, "name");
    std::cout << "Entity name: " << lua_tostring(l, 2) << std::endl;
    //Pop the name off
    lua_pop(l, 1);
    
    //Can i do references to functions?
    lua_getfield(l, 1, "speak");
    LuaRef fcnRef(l, -1);
    //Clear stack
    lua_pop(l, 2);
    sA.stackDump(l);

    //Try calling the function with the self table as param
    fcnRef.Push();
    entityRef.Push();
    sA.stackDump(l);
    if (lua_pcall(l, 1, 0, 0) != 0)
        std::cout << "Error calling: Entity:speak :" << lua_tostring(l, -1) << std::endl;

    //Get a reference system pointer to the entity
    //int entityRef = luaL_ref(l, LUA_REGISTRYINDEX);
    ////Stack is now empty, object has been popped and referenced
    //sA.stackDump(l);

    ////Get the referenced item onto the stack
    //lua_rawgeti(l, LUA_REGISTRYINDEX, entityRef);
    ////Try getting the name field
    //lua_getfield(l, 1, "name");
    ////Dump stack
    //sA.stackDump(l);
    ////Print entity's name field
    //std::cout << "Entity name: " << lua_tostring(l, 2) << std::endl;

    ////Pop the name off
    //lua_pop(l, 1);
    //sA.stackDump(l);
    //
    ////Try to call metamethod function Entity:speak()
    //lua_getfield(l, 1, "speak");
    ////Push table as an arguement
    //lua_pushvalue(l, 1);
    ////Call the function
    //if (lua_pcall(l, 1, 0, 0) != 0)
    //    std::cout << "Error calling: Entity:speak :" << lua_tostring(l, -1) << std::endl;

    ////Clear stack and unreference the entity
    //lua_pop(l, 1);
    //luaL_unref(l, LUA_REGISTRYINDEX, entityRef);

    ////Make sure the entity still exists
    //lua_getglobal(l, "entity");
    //lua_getfield(l, 1, "name");
    //std::cout << "Re-gotten Entity name: " << lua_tostring(l, 2) << std::endl;
    //sA.stackDump(l);

    return 0;
}