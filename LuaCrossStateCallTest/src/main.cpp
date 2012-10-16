#include <iostream>
#include "luascript.h"
#include "vectors.h"

int main(int argc, char** argv){
    //The two scripts we'll be using to test this
    LuaScript scriptA("../scripts/scriptA.lua");
    LuaScript scriptB("../scripts/scriptB.lua");

    std::cout << "ScriptA name: " << scriptA.Name()
        << "\nScriptB name: " << scriptB.Name() << std::endl;

    return 0;
}