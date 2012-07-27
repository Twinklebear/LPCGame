#include <fstream>
#include <string>
#include <memory>
#include "json/json.h"
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
	mMap.reset(new Map());
	mManager.reset(new GameObjectManager());
	mCamera.reset(new Camera());

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
		mManager->Update();
		mManager->SetCollisionMaps(mMap.get());

		float deltaT = mDelta.GetTicks() / 1000.f;
		mManager->Move(deltaT);

		mDelta.Start();

		///RENDERING
		Window::Clear();
		mMap->Draw();
		mManager->Draw();

		Window::Present();
	}
	return mExitCode;
}
void GameState::Free(){
	Input::RemoveManager();
	mMap.reset();
	mManager.reset();
}
Json::Value GameState::Save(){
	Json::Value val;
	val["map"] 	   = mMap->Save();
	val["objects"] = mManager->Save();
	val["name"]	   = mName;

	Free();
	return val;
}
void GameState::Load(Json::Value value){
	Init();
	mName = value["name"].asString();
	mMap->Load(value["map"]);
	//Load the objects
	Json::Value objects = value["objects"];
	for (int i = 0; i < objects.size(); ++i){
		if (objects[i]["obj"].asString() == "player"){
			Player *p = new Player();
			p->Load(objects[i]);
			std::shared_ptr<GameObject> sObj(p);
			//Set player as camera focuse
			mCamera->SetFocus(sObj);
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