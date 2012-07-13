#include "SDL.h"
#include "input.h"

SDL_Event Input::event;
bool Input::fDown;
bool Input::wDown;
bool Input::aDown;
bool Input::sDown;
bool Input::dDown;
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
				case SDLK_w:
					wDown = true;
					break;
				case SDLK_a:
					aDown = true;
					break;
				case SDLK_s:
					sDown = true;
					break;
				case SDLK_d:
					dDown = true;
					break;
				case SDLK_f: 
					fDown = true;
					break;
				case SDLK_ESCAPE:
					mQuit = true;
					break;
				default:
					break;
			}
		}
		if (event.type == SDL_KEYUP){
			switch (event.key.keysym.sym){
				case SDLK_w:
					wDown = false;
					break;
				case SDLK_a:
					aDown = false;
					break;
				case SDLK_s:
					sDown = false;
					break;
				case SDLK_d:
					dDown = false;
					break;
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
		case 'w':
			return wDown;
		case 'a':
			return aDown;
		case 's':
			return sDown;
		case 'd':
			return dDown;
		case 'f':
			return fDown;
		default:
			return false;
	}
}
bool Input::Quit(){
	return mQuit;
}