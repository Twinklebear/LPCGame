#include <iostream>
#include <string>
#include <map>
//#include "luascript.h"
#include "luacscript.h"
#include "vectors.h"

int main(int argc, char** argv){
    //The two scripts we'll be using to test this
    //LuaScript scriptA("../scripts/scriptA.lua");
    //LuaScript scriptB("../scripts/scriptB.lua");
    LuaCScript sA("../res/scripts/scriptA.lua");
    LuaCScript sB("../res/scripts/scriptB.lua");
    return 0;
}