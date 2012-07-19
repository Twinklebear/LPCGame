#include <stdexcept>
#include <thread>
#include <mutex>
#include "rect.h"
#include "vectors.h"
#include "physics.h"
#include "map.h"
#include "objectpool.h"
#include "window.h"
#include "gameobjectmanager.h"
#include "timer.h"
#include "image.h"
#include "player.h"
#include "npc.h"
#include "input.h"
#include "button.h"
#include "state.h"

#include "debugger.h"
#include <iostream>

int main(int argc, char** argv){
	//Initialize statics
	Window::Init();
	Input::Init();
	//Setup our game stuff
	Timer delta;
	Map *map		= new Map();
	Player *player	= new Player();
	GameObjectManager *manager = new GameObjectManager();

	//Register the objects with the manager
	player->Start(10, 10);
	manager->Register((GameObject*)player);

	//Setup initial collision maps
	manager->SetCollisionMaps(map);
	//Register the manager with input
	Input::RegisterManager(manager);

	delta.Start();
	while (!Input::Quit()){
		//EVENT POLLING
		Input::PollEvent();

		///LOGIC
		manager->Update();
		manager->SetCollisionMaps(map);

		float deltaT = delta.GetTicks() / 1000.f;
		manager->Move(deltaT);

		delta.Start();

		///RENDERING
		Window::Clear();
		map->Draw();
		manager->Draw();

		//refresh window
		Window::Present();
	}
	delete map;
	delete manager;

	Window::Quit();

	return 0;
}