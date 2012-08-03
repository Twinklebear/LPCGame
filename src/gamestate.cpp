#include <string>
#include <memory>
#include "../externals/json/json.h"
#include "gameobject.h"
#include "gameobjectmanager.h"
#include "window.h"
#include "input.h"
#include "timer.h"
#include "player.h"
#include "npc.h"
#include "objectbutton.h"
#include "gamestate.h"

GameState::GameState(){
}
GameState::~GameState(){
}
std::string GameState::Run(){
	//Unset quits from earlier
	Input::ClearQuit();
	//Cleanup any previous exit settings
	UnsetExit();

	Timer delta;
	delta.Start();
	while (!mExit){
		//EVENT POLLING
		Input::PollEvent();
		if (Input::Quit())
			SetExit("quit");
		if (Input::KeyDown(SDL_SCANCODE_ESCAPE))
			SetExit("mIntro");

		///LOGIC
		mCamera->Update();
		mManager->Update();
		mManager->SetCollisionMaps(mMap.get());
		mUiManager->Update();

		float deltaT = delta.GetTicks() / 1000.f;
		mManager->Move(deltaT);
		mUiManager->Move(deltaT);

		delta.Start();

		///RENDERING
		Window::Clear();
		mMap->Draw(mCamera.get());
		mManager->Draw();
		mUiManager->Draw();

		Window::Present();
	}
	Input::ClearKeys();

	return mExitCode;
}
void GameState::Init(){
	mMap 	   = std::shared_ptr<Map>(new Map());
	mManager   = std::shared_ptr<GameObjectManager>(new GameObjectManager());
	mUiManager = std::shared_ptr<UiObjectManager>(new UiObjectManager());
	mCamera    = std::shared_ptr<Camera>(new Camera());

	mManager->Register(mCamera);
	Input::RegisterManager(mManager);
	Input::RegisterManager(mUiManager);
}
void GameState::Free(){
	Input::FreeManagers();
	mMap.reset();
	mManager.reset();
	mUiManager.reset();
}
Json::Value GameState::Save(){
	Json::Value val = State::Save();
	val["map"] = mMap->Save();
	val["ui"]  =  mUiManager->Save();

	Free();
	return val;
}
void GameState::Load(Json::Value val){
	Init();
	State::Load(val);
	mMap->Load(val["map"]);
	//Set scene box
	mCamera->SetSceneBox(Rectf(0, 0, mMap->Box().w, mMap->Box().h));

	//Load the objects
	Json::Value objects = val["objects"];
	for (int i = 0; i < objects.size(); ++i){
		if (objects[i]["obj"].asString() == "player"){
			Player *p = new Player();
			p->Load(objects[i]);
			std::shared_ptr<GameObject> sObj(p);
			//Check for focus tag
			if (sObj->HasTag("focus"))
				mCamera->SetFocus(sObj);
			//Register
			mManager->Register(sObj);
		}
		if (objects[i]["obj"].asString() == "npc"){
			Npc *n = new Npc();
			n->Load(objects[i]);
			std::shared_ptr<GameObject> sObj(n);
			//Register with manager
			mManager->Register(sObj);
		}
	}
	//Load the ui elements
	Json::Value uiObj = val["ui"];
	for (int i = 0; i < uiObj.size(); ++i){
		//Loading object buttons
		if (uiObj[i]["type"].asString() == "objectbutton"){
			ObjectButton<State> *b = new ObjectButton<State>();
			b->RegisterCallBack(this, &State::SetExit, "");
			b->Load(uiObj[i]);
			std::shared_ptr<GameObject> sObj(b);
			mUiManager->Register(sObj);
		}
	}
}