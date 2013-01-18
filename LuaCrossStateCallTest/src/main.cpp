#include <iostream>
#include <string>
#include "luacscript.h"
#include "luaprimitiveparam.h"

//This project is more for general Lua tests/experiments at this point.

int main(int argc, char** argv){
    //The two scripts we'll be using to test this
    LuaCScript sA("../res/scripts/scriptA.lua");

    LuaC::StringParam strParam("Howder");
    std::vector<LuaC::LuaParam*> params;
    params.push_back(&strParam);
    std::string res = sA.CallFunction<LuaC::StringParam>("Test", params);
    sA.CallFunction("TestVoid", params);

    std::cout << "Got result: " << res << std::endl;

    //LuaCScript sB("../res/scripts/scriptB.lua");
    return 0;
}