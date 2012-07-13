#include "SDL.h"
#include "input.h"

SDL_Event Input::event;
bool Input::fDown;
bool Input::mQuit;

Input::Input(){
	mQuit = false;
}
Input::~Input(){}
void Input::PollEvent(){
	while(SDL_PollEvent(&event)){
		if (event.type == SDL_QUIT)
			mQuit = true;
		if (event.type == SDL_KEYDOWN){
			switch (event.key.keysym.sym){
				case SDLK_f: 
					fDown = true;
					break;
				default:
					break;
			}
		}
		if (event.type == SDL_KEYUP){
			switch (event.key.keysym.sym){
				case SDLK_f: 
					fDown = false;
					break;
				default:
					break;
			}
		}
	}
}
bool Input::KeyDown(char keyCode){
	switch (keyCode){
		case 'f':
			return fDown;
		default:
			return false;
	}
}
bool Input::Quit(){
	return mQuit;
}