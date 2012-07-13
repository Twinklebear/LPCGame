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
/*
//Handles the rendering thread
void Renderer(std::vector<GameObject*> *objects, Map *map, bool &quit){
	//Window::Setup();
	Timer fps;
	fps.Start();
	//the rendering loop
	while (!quit){
		Window::FillWhite();
		//map->Draw();

		for (GameObject *i : *objects)
			i->Draw();

		//refresh window
		try{
			Window::Flip();
		}
		catch (const std::runtime_error &e){
			std::cout << e.what() << std::endl;
			return;
		}
		
		//int ticks = fps.Restart();
		//if (ticks < 1000 / Window::FrameRateLimit()){
		//	SDL_Delay((1000 / Window::FrameRateLimit()) - ticks);
		//}
		
	}
}
*/
int main(int argc, char** argv){
	Window::Setup();
	SDL_Event event;
	Timer fps, delta;
	bool quit = false;

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

	fps.Start();
	delta.Start();

	//TODO: Make all SDL_Surface*'s into std::unique_ptr's with a custom deleter to free the surface?
	//TODO: Add collision checking between entities

	//Start up the rendering thread
	//std::thread *tRenderer = new std::thread(Renderer, &objects, map, quit);
	//tRenderer->detach();

	while (!Input::Quit()){
		//EVENT POLLING
		/*
		while (SDL_PollEvent(&event)){
			Window::HandleEvents(event);
			player->HandleEvents(event);
			if (event.type == SDL_QUIT || (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE))
				quit = true;
		}
		*/
		Input::PollEvent();
		if (Input::KeyDown('f')){
			std::cout << "f down" << std::endl;
		}

		///LOGIC
		manager->Update();
		manager->SetCollisionMaps(map);

		npc->SetMove(Math::DOWN);

		float deltaT = delta.GetTicks() / 1000.f;
		manager->Move(deltaT);

		delta.Start();
		///RENDERING
		Window::FillWhite();
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
		//Cap framerate
		int ticks = fps.Restart();
		if (ticks < 1000 / Window::FrameRateLimit()){
			SDL_Delay((1000 / Window::FrameRateLimit()) - ticks);
		}
	}
	delete map;
	delete player;
	delete npc;
	delete manager;

	return 0;
}