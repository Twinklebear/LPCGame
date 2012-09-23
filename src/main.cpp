#include <stdexcept>
#include <memory>
#include "window.h"
#include "input.h"
#include "statemanager.h"

#include <lua.hpp>

#include <iostream>
void TestFunc(){
    std::cout << "Test function ran." << std::endl;
}

//Trying something for lua
extern "C" int __declspec(dllexport) __cdecl luaopen_test(lua_State *l){
    using namespace luabind;

    std::cout << "Will load module Test" << std::endl;
    
    //open(l);
    module(l, "test")[
        def("TestFunc", &TestFunc)    
    ];

    return 0;
}

#undef main
int main(int argc, char** argv){
	//Initialize statics
	Window::Init();
	Input::Init();

	StateManager::InitIntro();

    Input::Close();
	Window::Quit();

	return 0;
}