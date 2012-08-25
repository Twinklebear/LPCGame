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
				def("KeyDown", (bool (*)(std::string))&Input::KeyDown),
				def("KeyDown", (bool (*)(int))&Input::KeyDown),
				def("Quit", &Input::Quit)
			]
			//To expose the SDL_Scancodes to Lua
			.enum_("Key")[
				value("KEY_1", SDL_SCANCODE_1),
				value("KEY_2", SDL_SCANCODE_2),
				value("KEY_3", SDL_SCANCODE_3),
				value("KEY_4", SDL_SCANCODE_4),
				value("KEY_5", SDL_SCANCODE_5),
				value("KEY_6", SDL_SCANCODE_6),
				value("KEY_7", SDL_SCANCODE_7),
				value("KEY_8", SDL_SCANCODE_8),
				value("KEY_9", SDL_SCANCODE_9),
				value("KEY_0", SDL_SCANCODE_0),
				value("KEY_Q", SDL_SCANCODE_Q),
				value("KEY_W", SDL_SCANCODE_W),
				value("KEY_E", SDL_SCANCODE_E),
				value("KEY_R", SDL_SCANCODE_R),
				value("KEY_T", SDL_SCANCODE_T),
				value("KEY_Y", SDL_SCANCODE_Y),
				value("KEY_U", SDL_SCANCODE_U),
				value("KEY_I", SDL_SCANCODE_I),
				value("KEY_O", SDL_SCANCODE_O),
				value("KEY_P", SDL_SCANCODE_P),
				value("KEY_A", SDL_SCANCODE_A),
				value("KEY_S", SDL_SCANCODE_S),
				value("KEY_D", SDL_SCANCODE_D),
				value("KEY_F", SDL_SCANCODE_F),
				value("KEY_G", SDL_SCANCODE_G),
				value("KEY_H", SDL_SCANCODE_H),
				value("KEY_J", SDL_SCANCODE_J),
				value("KEY_K", SDL_SCANCODE_K),
				value("KEY_L", SDL_SCANCODE_L),
				value("KEY_Z", SDL_SCANCODE_Z),
				value("KEY_X", SDL_SCANCODE_X),
				value("KEY_C", SDL_SCANCODE_C),
				value("KEY_V", SDL_SCANCODE_V),
				value("KEY_B", SDL_SCANCODE_B),
				value("KEY_N", SDL_SCANCODE_N),
				value("KEY_M", SDL_SCANCODE_M),
				value("KEY_SPACE", SDL_SCANCODE_SPACE),
				value("KEY_UP", SDL_SCANCODE_UP),
				value("KEY_DOWN", SDL_SCANCODE_DOWN),
				value("KEY_LEFT", SDL_SCANCODE_LEFT),
				value("KEY_RIGHT", SDL_SCANCODE_RIGHT)
			]
	];
}