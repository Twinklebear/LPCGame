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
	Input::RegisterManager(mManager);
}
std::string MenuState::Run(){
	//Unset events from earlier
	Input::Clear();
	//Clean up any previous exit settings
	UnsetExit();

	while (!mExit){
		//EVENT POLLING
		Input::PollEvent();
		if (Input::Quit())
			SetExit("quit");
		if (Input::KeyDown(SDL_SCANCODE_ESCAPE))
			SetExit("quit");
		if (Input::MouseClick(Input::MOUSE::LEFT)){
			Debugger::Write("Left clicked!");
			Debugger::Write("At location: ");
			Vector2i pos = Input::MousePos();
			Debugger::Write("\tx: ", pos.x);
			Debugger::Write("\ty: ", pos.y);
		}
		if (Input::MouseClick(Input::MOUSE::MIDDLE)){
			Debugger::Write("Middle click");
			Debugger::Write("At location: ");
			Vector2i pos = Input::MousePos();
			Debugger::Write("\tx: ", pos.x);
			Debugger::Write("\ty: ", pos.y);
		}
		if (Input::MouseClick(Input::MOUSE::RIGHT)){
			Debugger::Write("Right click");
			Debugger::Write("At location: ");
			Vector2i pos = Input::MousePos();
			Debugger::Write("\tx: ", pos.x);
			Debugger::Write("\ty: ", pos.y);
		}
		if (Input::MouseMotionOccured()){
			Debugger::Write("Mouse Motion!");
			Debugger::Write("Mouse pos: ");
			SDL_MouseMotionEvent e = Input::MouseMotion();
			Debugger::Write("\tPos x: ", e.x);
			Debugger::Write("\tPos y: ", e.y);
			Debugger::Write("\tRel x: ", e.xrel);
			Debugger::Write("\tRel y: ", e.yrel);
		}

		///LOGIC
		mCamera->Update();
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
	Input::FreeManagers();
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