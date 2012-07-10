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
#include "timer.h"
#include "image.h"
#include "player.h"
#include "npc.h"

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
int main(int argc, char* argv[]){
	Window::Setup();
	SDL_Event event;
	Timer fps, delta;
	bool quit = false;

	//Npc test
	Map *map		= new Map();
	Player *player	= new Player();
	//Npc *npc		= new Npc();

	fps.Start();
	delta.Start();

	//TODO: Some non-solid tiles are falsely being read as solid into the collision map
	//TODO: Make all SDL_Surface*'s into std::unique_ptr's with a custom deleter to free the surface?

	//vector of gameobject for grouping repetitive calls to them
	std::vector<GameObject*> objects;
	objects.push_back((GameObject*)player);
	//objects.push_back((GameObject*)npc);

	//setup initial collision maps
	for (GameObject *i : objects)
		i->SetCollisionMap(map->GetLocalCollisionMap(i->Box()));

	//Start up the rendering thread
	//std::thread *tRenderer = new std::thread(Renderer, &objects, map, quit);
	//tRenderer->detach();

	while (!quit){
		//EVENT POLLING
		while (SDL_PollEvent(&event)){
			Window::HandleEvents(event);
			player->HandleEvents(event);
			if (event.type == SDL_QUIT || (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE))
				quit = true;
		}
		///LOGIC
		for (GameObject *i : objects)
			i->SetCollisionMap(map->GetLocalCollisionMap(i->Box()));

		//npc->SetMove(Math::DOWN);

		float deltaT = delta.GetTicks() / 1000.f;
		for (GameObject *i : objects)
			i->Move(deltaT);

		delta.Start();
		///RENDERING
		Window::FillWhite();
		map->Draw();
	
		for (GameObject *i : objects)
			i->Draw();

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
	//delete npc;

	return 0;
}