#include <iostream>
#include <string>
#include "luacscript.h"

//This project is more for general Lua tests/experiments at this point.

int main(int argc, char** argv){
    std::function<bool(lua_State*, int)> fcn = [](lua_State *l, int idx){ return lua_toboolean(l, idx) == 1; };
    //The two scripts we'll be using to test this
    //LuaCScript sA("../res/scripts/scriptA.lua");
    //LuaCScript sB("../res/scripts/scriptB.lua");
    return 0;
}