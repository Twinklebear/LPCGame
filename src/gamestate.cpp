#include <fstream>
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
#include "button.h"
#include "gamestate.h"

GameState::GameState(){
}
GameState::~GameState(){
}
void GameState::Init(){
	mMap 	   = std::shared_ptr<Map>(new Map());
	mManager   = std::shared_ptr<GameObjectManager>(new GameObjectManager());
	mUiManager = std::shared_ptr<UiObjectManager>(new UiObjectManager());
	mCamera    = std::shared_ptr<Camera>(new Camera());

	mManager->Register(mCamera);
	Input::RegisterManager(mManager);
}
std::string GameState::Run(){
	//Unset quits from earlier
	Input::ClearQuit();
	//Cleanup any previous exit settings
	UnsetExit();

	mDelta.Start();
	while (!mExit){
		//EVENT POLLING
		Input::PollEvent();
		if (Input::Quit())
			SetExit("mIntro");

		///LOGIC
		mCamera->Update();
		mManager->Update();
		mManager->SetCollisionMaps(mMap.get());

		float deltaT = mDelta.GetTicks() / 1000.f;
		mManager->Move(deltaT);

		mDelta.Start();

		///RENDERING
		Window::Clear();
		mMap->Draw(mCamera.get());
		mManager->Draw();

		Window::Present();
	}
	return mExitCode;
}
void GameState::Free(){
	Input::FreeManagers();
	mMap.reset();
	mManager.reset();
}
Json::Value GameState::Save(){
	Json::Value val = State::Save();
	val["map"] 	   = mMap->Save();

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
			if (sObj->HasTag("focus"))
				mCamera->SetFocus(sObj);
			//Set player as camera focuse
			//mCamera->SetFocus(sObj);
			//Register with manager
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
}