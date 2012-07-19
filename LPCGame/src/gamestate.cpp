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
	mMap = new Map();
	Player *player	= new Player();
	mManager = new GameObjectManager();

	player->Start(10, 10);
	mManager->Register((GameObject*)player);
}
//Run the state
void GameState::Run(){
	Input::RegisterManager(mManager);
	
	mDelta.Start();
	while (!Input::Quit()){
		//EVENT POLLING
		Input::PollEvent();

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
}
//Free the memory used by the state
void GameState::Free(){
	delete mMap;
	delete mManager;
}

