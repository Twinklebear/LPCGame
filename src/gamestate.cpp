#include <string>
#include <memory>
#include <thread>
#include <condition_variable>
#include <mutex>
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
	//Start the render and physics threads
	//std::thread tRend(&GameState::RenderThread, this);
	//std::thread tPhys(&GameState::PhysicsThread, this);
	//std::mutex m;

	Timer delta;
	//Unset events from earlier
	Input::Clear();
	//Cleanup any previous exit settings
	UnsetExit();

	delta.Start();
	while (!mExit){
		//EVENT POLLING
		Input::PollEvent();
		if (Input::Quit())
			SetExit("quit");
		if (Input::KeyDown(SDL_SCANCODE_ESCAPE))
			SetExit("mIntro");

		//Logic
		mCamera->Update();
		mManager->Update();
		mManager->SetCollisionMaps(mMap.get());
		mUiManager->Update();

		float deltaT = delta.Restart() / 1000.f;
		mManager->Move(deltaT);
		mUiManager->Move(deltaT);

		//Rendering
		Window::Clear();
		mMap->Draw(mCamera.get());
		mManager->Draw();
		mUiManager->Draw();

		Window::Present();
		
		//Wait for notification
		//std::unique_lock<std::mutex> lock(m);
		//mCondVar.wait(lock);
	}
	//Join the threads back in
	//tRend.join();
	//tPhys.join();

	return mExitCode;
}

void GameState::RenderThread(){
/*	while (!mExit){
		Window::Clear();
		mMap->Draw(mCamera.get());
		mManager->Draw();
		mUiManager->Draw();

		Window::Present();
		//Notify waiting threads
		mCondVar.notify_all();
	}
*/
}
void GameState::PhysicsThread(){
/*
	Timer delta;
	std::mutex m;
	//Start timer and loop
	delta.Start();
	while (!mExit){
		mCamera->Update();
		mManager->Update();
		mManager->SetCollisionMaps(mMap.get());
		mUiManager->Update();

		float deltaT = delta.Restart() / 1000.f;
		mManager->Move(deltaT);
		mUiManager->Move(deltaT);

		//Wait for notification
		std::unique_lock<std::mutex> lock(m);
		mCondVar.wait(lock);
	}
*/
}
void GameState::Init(){
	mMap 	   = std::shared_ptr<Map>(new Map());
	mManager   = std::shared_ptr<GameObjectManager>(new GameObjectManager());
	mUiManager = std::shared_ptr<UiObjectManager>(new UiObjectManager());
	mCamera    = std::shared_ptr<Camera>(new Camera());

	mManager->Register(mCamera);
}
void GameState::Free(){
	//We don't reset the shared pts b/c then they don't delete the object
	//when destroyed, and we get leaks
	//mMap.reset();
	//mManager.reset();
	//mUiManager.reset();
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