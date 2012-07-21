#include "gameobject.h"
#include "gameobjectmanager.h"
#include "window.h"
#include "input.h"
#include "button.h"
#include "objectbutton.h"
#include "menustate.h"
#include "statemanager.h"

#include "debugger.h"

MenuState::MenuState(){
	Init();	
}
MenuState::~MenuState(){
	Free();
}
void MenuState::Init(){
	//Create two buttons
	Button *play = new Button(200, 100, "Play");
	Button *quit = new Button(200, 300, "Quit");
	play->RegisterCallBack(StateManager::SetActiveState, StateManager::IdFromName("game"));

	mManager = new GameObjectManager();
	mManager->Register((GameObject*)play);
	mManager->Register((GameObject*)quit);

	//Testing
	ObjectButton<MenuState> *testButton = new ObjectButton<MenuState>(200, 500, "TEST");
	testButton->RegisterCallBack(this, &MenuState::CallTest, 0);
	mManager->Register((GameObject*)testButton);

	dbg = new Debugger("menustate.txt");
}
void MenuState::Run(){
	Input::RegisterManager(mManager);
	mExit = false;
	while (!Input::Quit() && !mExit){
		//EVENT POLLING
		Input::PollEvent();

		///LOGIC
		mManager->Update();

		///RENDERING
		Window::Clear();
		mManager->Draw();

		//refresh window
		Window::Present();
	}
}
void MenuState::Free(){
	delete dbg;
	delete mManager;
}
void MenuState::CallTest(int a){
	mExit = true;
}
std::string MenuState::Serialize(){
	return "";
}