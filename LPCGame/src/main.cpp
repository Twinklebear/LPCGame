#include <stdexcept>
#include <thread>
#include <mutex>
#include "SDL.h"
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

#include "debugger.h"
#include <iostream>

void CallBack(){
	Debugger dbg("callback.txt");
	dbg.Write("Got called");
}

int main(int argc, char** argv){
	//Initialize statics
	Window::Init();
	Input::Init();
	//Setup our game stuff
	Timer delta;
	Map *map		= new Map();
	Player *player	= new Player();
	Npc *npc		= new Npc();
	Button *button	= new Button();
	GameObjectManager *manager = new GameObjectManager();

	//Register the objects with the manager
	player->Start(10, 10);
	npc->Start(100, 100);
	button->Start(200, 200);
	button->RegisterCallBack(*CallBack);

	manager->Register((GameObject*)player);
	manager->Register((GameObject*)npc);
	manager->Register((GameObject*)button);
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
	delete button;
	delete manager;

	Window::Quit();

	return 0;
}