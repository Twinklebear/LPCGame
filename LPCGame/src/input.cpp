#include "SDL.h"
#include "window.h"
#include "gameobjectmanager.h"
#include "input.h"

SDL_Event Input::evt;
GameObjectManager* Input::mManager;
Uint8* Input::mKeyStates;
bool Input::mQuit;

Input::Input(){}
Input::~Input(){}
void Input::Init(){
	mQuit = false;
	mManager = nullptr;
	mKeyStates = SDL_GetKeyboardState(NULL);
}
void Input::PollEvent(){
	while(SDL_PollEvent(&evt)){
		//this is an ok method to do this. But maybe not the best
		Window::HandleEvents(evt);

		if (evt.type == SDL_QUIT || (evt.type == SDL_KEYDOWN && evt.key.keysym.sym == SDLK_ESCAPE))
			mQuit = true;

		if ((evt.type == SDL_MOUSEBUTTONDOWN || evt.type == SDL_MOUSEBUTTONUP) && mManager != nullptr){
			mManager->HandleMouseEvent(evt.button);
		}

	}
}
bool Input::KeyDown(char keyCode){
	SDL_PumpEvents();
	switch (keyCode){
		case 'w':
			return mKeyStates[SDL_SCANCODE_W];
		case 'a':
			return mKeyStates[SDL_SCANCODE_A];
		case 's':
			return mKeyStates[SDL_SCANCODE_S];
		case 'd':
			return mKeyStates[SDL_SCANCODE_D];
		case 'f':
			return mKeyStates[SDL_SCANCODE_F];
		default:
			return false;
	}
}
bool Input::Quit(){
	return mQuit;
}
void Input::RegisterManager(GameObjectManager *manager){
	mManager = manager;
}