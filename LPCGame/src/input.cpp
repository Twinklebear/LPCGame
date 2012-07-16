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
		if (evt.type == SDL_MOUSEMOTION && mManager != nullptr){
			mManager->HandleMouseEvent(evt.motion);
		}
	}
}
bool Input::KeyDown(char keyCode){
	SDL_PumpEvents();
	switch (keyCode){
		case '1':
			return mKeyStates[SDL_SCANCODE_1];
		case '2':
			return mKeyStates[SDL_SCANCODE_2];
		case '3':
			return mKeyStates[SDL_SCANCODE_3];
		case '4':
			return mKeyStates[SDL_SCANCODE_4];
		case '5':
			return mKeyStates[SDL_SCANCODE_5];
		case '6':
			return mKeyStates[SDL_SCANCODE_6];
		case '7':
			return mKeyStates[SDL_SCANCODE_7];
		case '8':
			return mKeyStates[SDL_SCANCODE_8];
		case '9':
			return mKeyStates[SDL_SCANCODE_9];
		case '0':
			return mKeyStates[SDL_SCANCODE_0];	
		case 'q':
			return mKeyStates[SDL_SCANCODE_Q];
		case 'w':
			return mKeyStates[SDL_SCANCODE_W];
		case 'e':
			return mKeyStates[SDL_SCANCODE_E];
		case 'r':
			return mKeyStates[SDL_SCANCODE_R];
		case 't':
			return mKeyStates[SDL_SCANCODE_T];
		case 'y':
			return mKeyStates[SDL_SCANCODE_Y];
		case 'u':
			return mKeyStates[SDL_SCANCODE_U];
		case 'i':
			return mKeyStates[SDL_SCANCODE_I];
		case 'o': 
			return mKeyStates[SDL_SCANCODE_O];
		case 'p':
			return mKeyStates[SDL_SCANCODE_P];
		case 'a':
			return mKeyStates[SDL_SCANCODE_A];
		case 's':
			return mKeyStates[SDL_SCANCODE_S];
		case 'd':
			return mKeyStates[SDL_SCANCODE_D];
		case 'f':
			return mKeyStates[SDL_SCANCODE_F];
		case 'g':
			return mKeyStates[SDL_SCANCODE_G];
		case 'h':
			return mKeyStates[SDL_SCANCODE_H];
		case 'j':
			return mKeyStates[SDL_SCANCODE_J];
		case 'k':
			return mKeyStates[SDL_SCANCODE_K];
		case 'l':
			return mKeyStates[SDL_SCANCODE_L];
		case 'z':
			return mKeyStates[SDL_SCANCODE_Z];
		case 'x':
			return mKeyStates[SDL_SCANCODE_X];
		case 'c':
			return mKeyStates[SDL_SCANCODE_C];
		case 'v':
			return mKeyStates[SDL_SCANCODE_V];
		case 'b':
			return mKeyStates[SDL_SCANCODE_B];
		case 'n':
			return mKeyStates[SDL_SCANCODE_N];
		case 'm':
			return mKeyStates[SDL_SCANCODE_M];
		case ' ':
			return mKeyStates[SDL_SCANCODE_SPACE];
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