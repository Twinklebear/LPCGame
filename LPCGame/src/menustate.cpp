#include "json/json.h"
#include "gameobject.h"
#include "gameobjectmanager.h"
#include "window.h"
#include "input.h"
#include "button.h"
#include "objectbutton.h"
#include "menustate.h"
#include "statemanager.h"

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
	play->RegisterCallBack(StateManager::SetActiveState, "game");

	mManager = new GameObjectManager();
	mManager->Register((GameObject*)play);
	mManager->Register((GameObject*)quit);

	Input::RegisterManager(mManager);
}
void MenuState::Run(){
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
	Input::RemoveManager();
	delete mManager;
}
void MenuState::Save(){

}