#include <memory>
#include "../externals/json/json.h"
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
}
MenuState::~MenuState(){
}
void MenuState::Init(){
	mManager = std::shared_ptr<GameObjectManager>(new GameObjectManager());
	mCamera  = std::shared_ptr<Camera>(new Camera());

	mManager->Register(mCamera);
	//Input::RegisterManager(mManager);
}
std::string MenuState::Run(){
	//Unset events from earlier
	Input::Clear();
	//Clean up any previous exit settings
	UnsetExit();

	Timer delta;
	delta.Start();
	while (!mExit){
		//EVENT POLLING
		Input::PollEvent();
		if (Input::Quit())
			SetExit("quit");
		if (Input::KeyDown(SDL_SCANCODE_ESCAPE))
			SetExit("quit");

		//Testing camera panning
		if (Input::KeyDown('q')){
			mCamera->Pan("test");
		}

		//LOGIC
		mCamera->Update();
		mManager->Update();

		float deltaT = delta.Restart() / 1000.f;
		mCamera->Move(deltaT);



		//RENDERING
		Window::Clear();
		mManager->Draw();

		//refresh window
		Window::Present();
	}
	return mExitCode;
}
void MenuState::Free(){
	mManager.reset();
}
Json::Value MenuState::Save(){
	Json::Value val = State::Save();

	Free();
	return val;
}
void MenuState::Load(Json::Value val){
	Init();
	State::Load(val);

	//Load the objects
	Json::Value objects = val["objects"];
	for (int i = 0; i < objects.size(); ++i){
		//Loading object buttons
		if (objects[i]["type"].asString() == "objectbutton"){
			ObjectButton<State> *b = new ObjectButton<State>();
			b->RegisterCallBack(this, &State::SetExit, "");
			b->Load(objects[i]);
			std::shared_ptr<GameObject> sObj(b);
			mManager->Register(sObj);
		}
	}
}