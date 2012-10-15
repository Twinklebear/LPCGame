#include <stdexcept>
#include <memory>
#include "window.h"
#include "input.h"
#include "statemanager.h"
#include "debug.h"

#undef main
int main(int argc, char** argv){
	//Initialize statics
    try {
	    Window::Init();
    }
    catch (const std::runtime_error &e){
        Debug::Log(e.what());
    }
    Debug::Init();
	Input::Init();

	StateManager::InitIntro();

    Input::Close();
    Debug::Quit();
	Window::Quit();

	return 0;
}