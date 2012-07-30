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
	Input::RemoveManager();
	mManager.reset();
}
Json::Value MenuState::Save(){
	Json::Value val;
	val["objects"]  = mManager->Save();
	val["name"]	    = mName;
	val["sceneBox"] = mSceneBox.Save();

	Free();
	return val;
}
void MenuState::Load(Json::Value val){
	Init();
	mName = val["name"].asString();
	mSceneBox.Load(val["sceneBox"]);
	mCamera->SetSceneBox(mSceneBox);

	//Load the objects
	Json::Value objects = val["objects"];
	for (int i = 0; i < objects.size(); ++i){
		//Loading object buttons
		if (objects[i]["type"].asString() == "objectbutton"){
			ObjectButton<MenuState> *b = new ObjectButton<MenuState>();
			b->RegisterCallBack(this, &MenuState::SetExit, "");
			b->Load(objects[i]);
			std::shared_ptr<GameObject> sObj(b);
			mManager->Register(sObj);
		}
	}
}