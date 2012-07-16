#include <stdexcept>
#include <thread>
#include <mutex>
#include "SDL.h"
#include "rect.h"
#include "vectors.h"
#include "physics.h"
#include "map.h"
//#include "objectpool.h"
#include "window.h"
#include "gameobjectmanager.h"
#include "timer.h"
#include "image.h"
#include "player.h"
#include "npc.h"
#include "input.h"

#include <iostream>

int main(int argc, char** argv){
	Window::Init();
	Timer delta;
	Map *map		= new Map();
	Player *player	= new Player();
	Npc *npc		= new Npc();
	GameObjectManager *manager = new GameObjectManager();
	//Register the objects with the manager
	player->Start(10, 10);
	npc->Start(100, 100);
	manager->Register((GameObject*)player);
	manager->Register((GameObject*)npc);
	//Setup initial collision maps
	manager->SetCollisionMaps(map);

	delta.Start();

	while (!Input::Quit()){
		//EVENT POLLING
		Input::PollEvent();

		///LOGIC
		manager->Update();
		manager->SetCollisionMaps(map);

		npc->SetMove(Math::DOWN);

		float deltaT = delta.GetTicks() / 1000.f;
		manager->Move(deltaT);

		delta.Start();

		///RENDERING
		Window::Clear();
		map->Draw();
		manager->Draw();

		//refresh window
		try{
			Window::Flip();
		}
		catch (const std::runtime_error &e){
			std::cout << e.what() << std::endl;
			return 1;
		}
	}
	delete map;
	delete player;
	delete npc;
	delete manager;

	Window::Quit();

	return 0;
}