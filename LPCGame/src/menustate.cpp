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
	//Button to play the game
	ObjectButton<MenuState> *play = new ObjectButton<MenuState>(200, 100, "Play");
	play->RegisterCallBack(this, &MenuState::SetExit, "gGame");
	//Button to quit
	ObjectButton<MenuState> *quit = new ObjectButton<MenuState>(200, 300, "Quit");
	quit->RegisterCallBack(this, &MenuState::SetExit, "quit");

	mManager = new GameObjectManager();
	mManager->Register((GameObject*)play);
	mManager->Register((GameObject*)quit);

	Input::RegisterManager(mManager);
}
std::string MenuState::Run(){
	//Unset quits from earlier
	Input::ClearQuit();
	//Clean up any previous exit settings
	UnsetExit();

	while (!mExit){
		//EVENT POLLING
		Input::PollEvent();
		if (Input::Quit())
			SetExit("quit");

		///LOGIC
		mManager->Update();

		///RENDERING
		Window::Clear();
		mManager->Draw();

		//refresh window
		Window::Present();
	}
	return mExitCode;
}
void MenuState::Free(){
	Input::RemoveManager();
	delete mManager;
}
Json::Value MenuState::Save(){
	Json::Value val;
	
	//Write the data to string
	//Json::StyledWriter writer;
	//std::string data = writer.write(root);
	
	return val;
}
void MenuState::Load(Json::Value value){
	
}