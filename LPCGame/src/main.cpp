#include <stdexcept>
#include <thread>
#include <mutex>
#include "SDL.h"
#include "rect.h"
#include "vectors.h"
#include "physics.h"
#include "map.h"
#include "window.h"
#include "timer.h"
#include "image.h"
#include "player.h"
#include "npc.h"

#include <iostream>

int main(int argc, char* argv[]){
	Window::Setup();	
	SDL_Event event;

	Map map;
	Timer fps, delta;
	bool quit = false;

	//Npc test
	Player *player = new Player();
	Npc *npc = new Npc();

	fps.Start();
	delta.Start();

	//vector of gameobject for grouping repetitive calls to them
	std::vector<GameObject*> objects;
	objects.push_back((GameObject*)player);
	objects.push_back((GameObject*)npc);

	//setup initial collision maps
	//for (GameObject *i : objects)
	//	i->SetCollisionMap(map.GetLocalCollisionMap(i->Box()));
	objects.at(0)->SetCollisionMap(map.GetLocalCollisionMap(player->Box()));
	objects.at(1)->SetCollisionMap(map.GetLocalCollisionMap(npc->Box()));

	while (!quit){
		//EVENT POLLING
		while (SDL_PollEvent(&event)){
			Window::HandleEvents(event);
			player->HandleEvents(event);
			if (event.type == SDL_QUIT || (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE))
				quit = true;
		}
		///LOGIC
		objects.at(0)->SetCollisionMap(map.GetLocalCollisionMap(player->Box()));
		objects.at(1)->SetCollisionMap(map.GetLocalCollisionMap(npc->Box()));

		//player.SetCollisionMap(map.GetLocalCollisionMap(player.Box()));
		//player->Move(delta.GetTicks() / 1000.f);

		//npc test
		npc->SetMove(Math::DOWN);
		//npcTest.Move(delta.GetTicks() / 1000.f);
		float deltaT = delta.GetTicks() / 1000.f;
		for (GameObject *i : objects)
			i->Move(deltaT);

		delta.Start();
		///RENDERING
		Window::FillWhite();
		map.Draw();
		//player.Draw();
		//npcTest.Draw();

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

	delete player;
	delete npc;

	return 0;
}