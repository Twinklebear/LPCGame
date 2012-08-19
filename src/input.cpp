#include <memory>
#include <string>
#include <SDL.h>
#include <luabind\luabind.hpp>
#include "window.h"
#include "input.h"

SDL_Event Input::evt;
Uint8* Input::mKeyStates;
SDL_MouseButtonEvent Input::mButtonEvt;
SDL_MouseMotionEvent Input::mMotionEvt;
bool Input::mQuit = false;
bool Input::mMouseMove = false;
bool Input::mMouseClick = false;

Input::Input(){}
Input::~Input(){}
void Input::Init(){
	mKeyStates = SDL_GetKeyboardState(NULL);
}
void Input::PollEvent(){
	//Clear mouse data
	ClearMouse();

	//Read the event stack
	while(SDL_PollEvent(&evt)){
		//this is an ok method to do this. But maybe not the best
		Window::HandleEvents(evt);

		if (evt.type == SDL_QUIT)
			mQuit = true;
		//Send mouse click events
		if ((evt.type == SDL_MOUSEBUTTONDOWN || evt.type == SDL_MOUSEBUTTONUP)){
			mMouseClick = true;
			mButtonEvt = evt.button;
		}
		//Send mouse movement events
		if (evt.type == SDL_MOUSEMOTION){
			mMouseMove = true;
			mMotionEvt = evt.motion;
		}
	}
}
/*
bool Input::KeyDown(std::string keyCode){
	switch (keyCode.at(0)){
		case '1':
			if (mKeyStates[SDL_SCANCODE_1] == 1)
				return true;
			else 
				return false;
		case '2':
			if (mKeyStates[SDL_SCANCODE_2] == 1)
				return true;
			else 
				return false;
		case '3':
			if (mKeyStates[SDL_SCANCODE_3] == 1)
				return true;
			else 
				return false;
		case '4':
			if (mKeyStates[SDL_SCANCODE_4] == 1)
				return true;
			else 
				return false;
		case '5':
			if (mKeyStates[SDL_SCANCODE_5] == 1)
				return true;
			else 
				return false;
		case '6':
			if (mKeyStates[SDL_SCANCODE_6] == 1)
				return true;
			else 
				return false;
		case '7':
			if (mKeyStates[SDL_SCANCODE_7] == 1)
				return true;
			else 
				return false;
		case '8':
			if (mKeyStates[SDL_SCANCODE_8] == 1)
				return true;
			else 
				return false;
		case '9':
			if (mKeyStates[SDL_SCANCODE_9] == 1)
				return true;
			else 
				return false;
		case '0':
			if (mKeyStates[SDL_SCANCODE_0] == 1)
				return true;
			else 
				return false;
		case 'q':
			if (mKeyStates[SDL_SCANCODE_Q] == 1)
				return true;
			else 
				return false;
		case 'w':
			if (mKeyStates[SDL_SCANCODE_W] == 1)
				return true;
			else 
				return false;
		case 'e':
			if (mKeyStates[SDL_SCANCODE_E] == 1)
				return true;
			else 
				return false;
		case 'r':
			if (mKeyStates[SDL_SCANCODE_R] == 1)
				return true;
			else 
				return false;
		case 't':
			if (mKeyStates[SDL_SCANCODE_T] == 1)
				return true;
			else 
				return false;
		case 'y':
			if (mKeyStates[SDL_SCANCODE_Y] == 1)
				return true;
			else 
				return false;
		case 'u':
			if (mKeyStates[SDL_SCANCODE_U] == 1)
				return true;
			else 
				return false;
		case 'i':
			if (mKeyStates[SDL_SCANCODE_I] == 1)
				return true;
			else 
				return false;
		case 'o': 
			if (mKeyStates[SDL_SCANCODE_O] == 1)
				return true;
			else 
				return false;
		case 'p':
			if (mKeyStates[SDL_SCANCODE_P] == 1)
				return true;
			else 
				return false;
		case 'a':
			if (mKeyStates[SDL_SCANCODE_A] == 1)
				return true;
			else 
				return false;
		case 's':
			if (mKeyStates[SDL_SCANCODE_S] == 1)
				return true;
			else 
				return false;
		case 'd':
			if (mKeyStates[SDL_SCANCODE_D] == 1)
				return true;
			else 
				return false;
		case 'f':
			if (mKeyStates[SDL_SCANCODE_F] == 1)
				return true;
			else 
				return false;
		case 'g':
			if (mKeyStates[SDL_SCANCODE_G] == 1)
				return true;
			else 
				return false;
		case 'h':
			if (mKeyStates[SDL_SCANCODE_H] == 1)
				return true;
			else 
				return false;
		case 'j':
			if (mKeyStates[SDL_SCANCODE_J] == 1)
				return true;
			else 
				return false;
		case 'k':
			if (mKeyStates[SDL_SCANCODE_K] == 1)
				return true;
			else 
				return false;
		case 'l':
			if (mKeyStates[SDL_SCANCODE_L] == 1)
				return true;
			else 
				return false;
		case 'z':
			if (mKeyStates[SDL_SCANCODE_Z] == 1)
				return true;
			else 
				return false;
		case 'x':
			if (mKeyStates[SDL_SCANCODE_X] == 1)
				return true;
			else 
				return false;
		case 'c':
			if (mKeyStates[SDL_SCANCODE_C] == 1)
				return true;
			else 
				return false;
		case 'v':
			if (mKeyStates[SDL_SCANCODE_V] == 1)
				return true;
			else 
				return false;
		case 'b':
			if (mKeyStates[SDL_SCANCODE_B] == 1)
				return true;
			else 
				return false;
		case 'n':
			if (mKeyStates[SDL_SCANCODE_N] == 1)
				return true;
			else 
				return false;
		case 'm':
			if (mKeyStates[SDL_SCANCODE_M] == 1)
				return true;
			else 
				return false;
		default:
			return false;
	}
}
*/
bool Input::KeyDown(int keyCode){
	if (mKeyStates[keyCode] == 1)
		return true;
	return false;
}
bool Input::MouseClick(int button){
	return (mMouseClick && mButtonEvt.button == button);
}
bool Input::MouseDown(int button){
	return ((SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(button)) != 0);
}

SDL_MouseButtonEvent Input::GetClick(){
	return mButtonEvt;
}
bool Input::MouseMotion(){
	//We can filter out the first event, which has false motion data by testing
	//if x == xrel and y = yrel, which only happens when starting the program
	return (mMouseMove && (mMotionEvt.x != mMotionEvt.xrel 
		&& mMotionEvt.y != mMotionEvt.yrel));
}
SDL_MouseMotionEvent Input::GetMotion(){
	return mMotionEvt;
}
Vector2f Input::MousePos(){
	Vector2i pos(0, 0);
	SDL_GetMouseState(&pos.x, &pos.y);
	return pos;
}
bool Input::Quit(){
	return mQuit;
}
void Input::Clear(){
	ClearQuit();
	ClearKeys();
	ClearMouse();
}
void Input::ClearQuit(){
	mQuit = false;
}
void Input::ClearKeys(){
	//I'm not sure if there's a better way to 0 out the values
	//for now this will do
	for (int i = 0; i < 282; ++i)
		mKeyStates[i] = 0;
}
void Input::ClearMouse(){
	mMouseClick = false;
	mMouseMove = false;
}
void Input::RegisterLua(lua_State* l){
	using namespace luabind;

	module(l, "LPC")[
		class_<Input>("Input")
			.scope[
				def("KeyDown", &Input::KeyDown),
				def("Quit", &Input::Quit)
			]
			//To expose the SDL_Scancodes to Lua
			.enum_("Key")[
				value("Key_1", SDL_SCANCODE_1),
				value("Key_2", SDL_SCANCODE_2),
				value("Key_3", SDL_SCANCODE_3),
				value("Key_4", SDL_SCANCODE_4),
				value("Key_5", SDL_SCANCODE_5),
				value("Key_6", SDL_SCANCODE_6),
				value("Key_7", SDL_SCANCODE_7),
				value("Key_8", SDL_SCANCODE_8),
				value("Key_9", SDL_SCANCODE_9),
				value("Key_0", SDL_SCANCODE_0),
				value("Key_Q", SDL_SCANCODE_Q),
				value("Key_W", SDL_SCANCODE_W),
				value("Key_E", SDL_SCANCODE_E),
				value("Key_R", SDL_SCANCODE_R),
				value("Key_T", SDL_SCANCODE_T),
				value("Key_Y", SDL_SCANCODE_Y),
				value("Key_U", SDL_SCANCODE_U),
				value("Key_I", SDL_SCANCODE_I),
				value("Key_O", SDL_SCANCODE_O),
				value("Key_P", SDL_SCANCODE_P),
				value("Key_A", SDL_SCANCODE_A),
				value("Key_S", SDL_SCANCODE_S),
				value("Key_D", SDL_SCANCODE_D),
				value("Key_F", SDL_SCANCODE_F),
				value("Key_G", SDL_SCANCODE_G),
				value("Key_H", SDL_SCANCODE_H),
				value("Key_J", SDL_SCANCODE_J),
				value("Key_K", SDL_SCANCODE_K),
				value("Key_L", SDL_SCANCODE_L),
				value("Key_Z", SDL_SCANCODE_Z),
				value("Key_X", SDL_SCANCODE_X),
				value("Key_C", SDL_SCANCODE_C),
				value("Key_V", SDL_SCANCODE_V),
				value("Key_B", SDL_SCANCODE_B),
				value("Key_N", SDL_SCANCODE_N),
				value("Key_M", SDL_SCANCODE_M),
				value("Key_Space", SDL_SCANCODE_SPACE),
				value("Key_Up", SDL_SCANCODE_UP),
				value("Key_Down", SDL_SCANCODE_DOWN),
				value("Key_Left", SDL_SCANCODE_LEFT),
				value("Key_Right", SDL_SCANCODE_RIGHT)
			]
	];
}