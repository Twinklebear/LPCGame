#include <fstream>
#include <string>
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
	//Player *player = new Player();
	mManager = new GameObjectManager();

	//player->Start(10, 10);
	//mManager->Register((GameObject*)player);

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

		//refresh window
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

	//Write the data to string
	//Json::StyledWriter writer;
	//std::string data = writer.write(root);
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
			mManager->Register((GameObject*)p);
		}
		if (objects[i]["obj"].asString() == "npc"){
			Npc *n = new Npc();
			n->Load(objects[i]);
			mManager->Register((GameObject*)n);
		}
	}
}