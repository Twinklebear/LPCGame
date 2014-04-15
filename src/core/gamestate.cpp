#include <string>
#include <memory>
#include "external/json/json.h"
#include "entity.h"
#include "entitymanager.h"
#include "window.h"
#include "input.h"
#include "timer.h"
#include "objectbutton.h"
#include "gamestate.h"

#include <iostream>

GameState::GameState(){
}
GameState::~GameState(){
}
std::string GameState::Run(){
	//Start the render and physics threads
	//std::thread tRend(&GameState::RenderThread, this);
	//std::thread tPhys(&GameState::PhysicsThread, this);
	//std::mutex m;
    	
	//Unset events from earlier
	Input::Clear();
	//Cleanup any previous exit settings
	UnsetExit();

    //Call the script's Init
    State::Init();

    Timer delta;
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
		float deltaT = delta.Restart() / 1000.f;
		mManager->Move(deltaT);

		//Rendering
		Window::Clear();
		mMap->Draw(mCamera);
		mManager->Draw();

		Window::Present();

        Window::ShowAvgFps(false);
		
		//Wait for notification
		//std::unique_lock<std::mutex> lock(m);
		//mCondVar.wait(lock);
	}
	//Join the threads back in
	//tRend.join();
	//tPhys.join();

	return mExitCode;
}
/*
void GameState::RenderThread(){
	while (!mExit){
		Window::Clear();
		mMap->Draw(mCamera.get());
		mManager->Draw();

		Window::Present();
		//Notify waiting threads
		mCondVar.notify_all();
	}
}
*/
/*
void GameState::PhysicsThread(){
	Timer delta;
	std::mutex m;
	//Start timer and loop
	delta.Start();
	while (!mExit){
		mCamera->Update();
		mManager->Update();
		mManager->SetCollisionMaps(mMap.get());

		float deltaT = delta.Restart() / 1000.f;
		mManager->Move(deltaT);

		//Wait for notification
		std::unique_lock<std::mutex> lock(m);
		mCondVar.wait(lock);
	}
}
*/
void GameState::Init(){
	mMap 	   = std::shared_ptr<Map>(new Map());
	mManager   = std::shared_ptr<EntityManager>(new EntityManager());
	mCamera    = std::shared_ptr<Camera>(new Camera());
	mTileSet   = std::shared_ptr<TileSet>(new TileSet());

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
    val["map"] = mMap->Filename();
	val["tileset"] = mTileSet->Save();

	Free();
	return val;
}
void GameState::Load(Json::Value val){
	Init();
	State::Load(val);
	mMap->Load(val["map"].asString());
	mTileSet->Load(val["tileset"]);
	mMap->LoadTileSet(mTileSet);
	//Set scene box
	mCamera->SetSceneBox(Rectf(0, 0, mMap->Box().w, mMap->Box().h));

	//Load the objects
	Json::Value entities = val["entities"];
	for (int i = 0; i < entities.size(); ++i){
        //Need to filter objectbuttons, special case for now soon they'll just
        //all be lua entities
        if (entities[i]["type"].asString() == "objectbutton"){
            ObjectButton<State> *b = new ObjectButton<State>();
			b->RegisterCallBack(this, &State::SetExit, "");
			b->Load(entities[i]);
			std::shared_ptr<Entity> sObj(b);
			mManager->Register(sObj);
        }
        else {
            std::shared_ptr<Entity> e = std::make_shared<Entity>(entities[i]["file"].asString());
            mManager->Register(e);
            e->Init(e);
        }
	}
}