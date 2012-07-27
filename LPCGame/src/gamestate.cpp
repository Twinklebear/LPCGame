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
	mMap = new Map();
	mManager = new GameObjectManager();

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
		mManager->SetCollisionMaps(mMap);

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
	delete mMap;
	delete mManager;
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
			mManager->Register(sObj);
		}
		if (objects[i]["obj"].asString() == "npc"){
			Npc *n = new Npc();
			n->Load(objects[i]);
			std::shared_ptr<GameObject> sObj(n);
			mManager->Register(sObj);
		}
	}
}