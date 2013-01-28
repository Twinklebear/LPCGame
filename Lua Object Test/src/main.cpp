#include <lua.hpp>
#include <iostream>
#include <string>
#include "luacscript.h"
#include "luaprimitiveparam.h"

int main(int argc, char** argv){
    //The two scripts we'll be using to test this
    LuaCScript sA("../res/scripts/scriptA.lua");

    //Get the raw state to mess with
    lua_State *l = sA.Get();
    lua_getglobal(l, "entity");
    //Get a reference system pointer to the entity
    int entityRef = luaL_ref(l, LUA_REGISTRYINDEX);
    //Stack is now empty, object has been popped and referenced
    sA.stackDump(l);

    //Get the referenced item onto the stack
    lua_rawgeti(l, LUA_REGISTRYINDEX, entityRef);
    //Try getting the name field
    lua_getfield(l, 1, "name");
    //Dump stack
    sA.stackDump(l);
    //Print entity's name field
    std::cout << "Entity name: " << lua_tostring(l, 2) << std::endl;

    //Pop the name off
    lua_pop(l, 1);
    sA.stackDump(l);
    
    //Try to call metamethod function Entity:speak()
    lua_getfield(l, 1, "speak");
    //Push table as an arguement
    lua_pushvalue(l, 1);
    //Call the function
    if (lua_pcall(l, 1, 0, 0) != 0)
        std::cout << "Error calling: Entity:speak :" << lua_tostring(l, -1) << std::endl;

    return 0;
}