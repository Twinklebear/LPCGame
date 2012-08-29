#include <stdexcept>
#include <memory>
#include "window.h"
#include "input.h"
#include "statemanager.h"

#include "debugger.h"
#undef main
int main(int argc, char** argv){
	//Initialize statics
	Window::Init();
	Input::Init();

	//Fire up debug output
	Debugger::Init();

	StateManager::InitIntro();

	Window::Quit();
	return 0;
}