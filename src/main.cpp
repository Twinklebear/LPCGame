#include <stdexcept>
#include <memory>
#include "window.h"
#include "input.h"
#include "statemanager.h"

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