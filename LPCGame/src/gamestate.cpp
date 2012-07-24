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
	Init();
}
GameState::~GameState(){
	Free();
}
void GameState::Init(){
	//Cleanup any previous exit settings
	UnsetExit();

	mMap = new Map();
	Player *player = new Player();
	mManager = new GameObjectManager();

	player->Start(10, 10);
	mManager->Register((GameObject*)player);

	Input::RegisterManager(mManager);
}
std::string GameState::Run(){
	//Unset quits from earlier
	Input::ClearQuit();

	mDelta.Start();
	while (!mExit){
		//EVENT POLLING
		Input::PollEvent();
		if (Input::Quit())
			SetExit("intro");
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
void GameState::Save(){
	Json::Value root;
	root["map"] = mMap->Save();

	//Write the data to string
	Json::StyledWriter writer;
	std::string data = writer.write(root);

	//Save the file to a file named the state's name
	std::ofstream file(("states/" + mName + ".json").c_str());
	file << data << std::endl;
	file.close();
}