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

#include <iostream>

int main(int argc, char* argv[]){
	Window::Setup();	
	SDL_Event event;
	Player player;
	Map map;
	Timer fps, delta;
	bool quit = false;

	fps.Start();
	delta.Start();

	player.SetCollisionMap(map.GetLocalCollisionMap(player.Box()));

	while (!quit){
		//EVENT POLLING
		while (SDL_PollEvent(&event)){
			Window::HandleEvents(event);
			player.HandleEvents(event);
			if (event.type == SDL_QUIT || (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE))
				quit = true;
		}
		///LOGIC
		player.SetCollisionMap(map.GetLocalCollisionMap(player.Box()));
		player.Move(delta.GetTicks() / 1000.f);

		delta.Start();
		///RENDERING
		Window::FillWhite();
		map.Draw();
		player.Draw();
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

	return 0;
}