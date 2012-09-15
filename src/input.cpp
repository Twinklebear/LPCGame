#include <memory>
#include <string>
#include <SDL.h>
#include <SDL_haptic.h>
#include <luabind\luabind.hpp>
#include "window.h"
#include "math.h"
#include "input.h"

SDL_Event Input::evt;
Uint8* Input::mKeyStates = nullptr;
SDL_Joystick* Input::mJoystick = nullptr;
SDL_MouseButtonEvent Input::mButtonEvt;
SDL_MouseMotionEvent Input::mMotionEvt;
bool Input::mQuit = false;
bool Input::mMouseMove = false;
bool Input::mMouseClick = false;

Input::Input(){}
Input::~Input(){}
void Input::Init(){
	mKeyStates = SDL_GetKeyboardState(NULL);
    //Init joystick
    if (SDL_NumJoysticks() > 0){
        //Some joystick testing info dump
        std::cout << "# Joysticks: " << SDL_NumJoysticks() << std::endl;
        //This number value should be changed? Support for multiple sticks?
        mJoystick = SDL_JoystickOpen(0);
        if (mJoystick != nullptr){
            std::cout << "Joystick 0 Dump:" << std::endl
                << "  Name: " << SDL_JoystickName(0) << std::endl
                << "  # Axes: " << SDL_JoystickNumAxes(mJoystick) << std::endl
                << "  # Buttons: " << SDL_JoystickNumButtons(mJoystick) << std::endl
                << "  # Balls: " << SDL_JoystickNumBalls(mJoystick) << std::endl
                << "  # Hats: " << SDL_JoystickNumHats(mJoystick) << std::endl;;
            //Testing force feedback
            std::cout << "Will now test force feedback" << std::endl;
            std::cout << "Joystick haptic status: " << SDL_JoystickIsHaptic(mJoystick) << std::endl;
            //Joystick only seems to be haptic when in DirectInput mode, and even then fails to play the effect
            SDL_Haptic *haptic = nullptr;
            int effectId;
            
            haptic = SDL_HapticOpenFromJoystick(mJoystick);
            if (haptic == nullptr){
                std::cout << "Couldn't open haptic on: " << SDL_JoystickName(0) << std::endl;
                return;
            }
            if ((SDL_HapticQuery(haptic) & SDL_HAPTIC_SINE) == 0){
                SDL_HapticClose(haptic);
                std::cout << "No sine effect available" << std::endl;
                return;
            }
            //Create the effect
            SDL_HapticEffect *effect = new SDL_HapticEffect;
            effect->type = SDL_HAPTIC_SINE;
            effect->periodic.direction.type = SDL_HAPTIC_POLAR;
            effect->periodic.direction.dir[0] = 18000;
            effect->periodic.period = 1000;
            effect->periodic.magnitude = 20000;
            effect->periodic.length = 5000;
            effect->periodic.attack_length = 1000;
            effect->periodic.fade_length = 1000;

            //Upload the effect
            effectId = SDL_HapticNewEffect(haptic, effect);
            SDL_HapticRunEffect(haptic, effectId, 1);
            SDL_Delay(5000);
            //Destroy the effect and close haptic
            SDL_HapticDestroyEffect(haptic, effectId);
            SDL_HapticClose(haptic);
        }
        else
            std::cout << "Failed to open joystick" << std::endl;
    }
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
			return (mKeyStates[SDL_SCANCODE_1] == 1);
		case '2':
			return (mKeyStates[SDL_SCANCODE_2] == 1);
		case '3':
			return (mKeyStates[SDL_SCANCODE_3] == 1);
		case '4':
			return (mKeyStates[SDL_SCANCODE_4] == 1);
		case '5':
			return (mKeyStates[SDL_SCANCODE_5] == 1);
		case '6':
			return (mKeyStates[SDL_SCANCODE_6] == 1);
		case '7':
			return (mKeyStates[SDL_SCANCODE_7] == 1);
		case '8':
			return (mKeyStates[SDL_SCANCODE_8] == 1);
		case '9':
			return (mKeyStates[SDL_SCANCODE_9] == 1);
		case '0':
			return (mKeyStates[SDL_SCANCODE_0] == 1);
		case 'q':
			return (mKeyStates[SDL_SCANCODE_Q] == 1);
		case 'w':
			return (mKeyStates[SDL_SCANCODE_W] == 1);
		case 'e':
			return (mKeyStates[SDL_SCANCODE_E] == 1);
		case 'r':
			return (mKeyStates[SDL_SCANCODE_R] == 1);
		case 't':
			return (mKeyStates[SDL_SCANCODE_T] == 1);
		case 'y':
			return (mKeyStates[SDL_SCANCODE_Y] == 1);
		case 'u':
			return (mKeyStates[SDL_SCANCODE_U] == 1);
		case 'i':
			return (mKeyStates[SDL_SCANCODE_I] == 1);
		case 'o': 
			return (mKeyStates[SDL_SCANCODE_O] == 1);
		case 'p':
			return (mKeyStates[SDL_SCANCODE_P] == 1);
		case 'a':
			return (mKeyStates[SDL_SCANCODE_A] == 1);
		case 's':
			return (mKeyStates[SDL_SCANCODE_S] == 1);
		case 'd':
			return (mKeyStates[SDL_SCANCODE_D] == 1);
		case 'f':
			return (mKeyStates[SDL_SCANCODE_F] == 1);
		case 'g':
			return (mKeyStates[SDL_SCANCODE_G] == 1);
		case 'h':
			return (mKeyStates[SDL_SCANCODE_H] == 1);
		case 'j':
			return (mKeyStates[SDL_SCANCODE_J] == 1);
		case 'k':
			return (mKeyStates[SDL_SCANCODE_K] == 1);
		case 'l':
			return (mKeyStates[SDL_SCANCODE_L] == 1);
		case 'z':
			return (mKeyStates[SDL_SCANCODE_Z] == 1);
		case 'x':
			return (mKeyStates[SDL_SCANCODE_X] == 1);
		case 'c':
			return (mKeyStates[SDL_SCANCODE_C] == 1);
		case 'v':
			return (mKeyStates[SDL_SCANCODE_V] == 1);
		case 'b':
			return (mKeyStates[SDL_SCANCODE_B] == 1);
		case 'n':
			return (mKeyStates[SDL_SCANCODE_N] == 1);
		case 'm':
			return (mKeyStates[SDL_SCANCODE_M] == 1);
		default:
			return false;
	}
}
bool Input::KeyDown(int keyCode){
	return (mKeyStates[keyCode] == 1);
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
float Input::GetJoyAxis(int axis){
    if (SDL_JoystickOpened(0) && axis < SDL_JoystickNumAxes(mJoystick)){
        //The valid values are -32768 to 32767 but i want it as a float from -1 to 1, so we divide
        float val = (SDL_JoystickGetAxis(mJoystick, axis) / 32767.0f);
        //Allow for some deadzone
        if (val < 0 && val > -0.01)
            return 0;
        else if (val < 0)
            return Math::Clamp(val, -1, 0);
        else if (val > 0 && val < 0.01)
            return 0;
        else if (val > 0)
            return Math::Clamp(val, 0, 1);
        else 
            return 0;
    }
    else
        return 0.0f;
}
bool Input::GetJoyButton(int button){
    if (SDL_JoystickOpened(0) && button < SDL_JoystickNumButtons(mJoystick)){
        return (SDL_JoystickGetButton(mJoystick, button) == 1);
    }
    else return false;
}
int Input::GetJoyHat(int hat){
    if (SDL_JoystickOpened(0) && hat < SDL_JoystickNumHats(mJoystick)){
        return SDL_JoystickGetHat(mJoystick, hat);
    }
    else
        return SDL_HAT_CENTERED;
}
bool Input::Quit(){
	return mQuit;
}
void Input::Clear(){
	ClearQuit();
	ClearKeys();
	ClearMouse();
}
void Input::Close(){
    if (SDL_JoystickOpened(0) == 1)
        SDL_JoystickClose(mJoystick);
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
                def("GetJoyAxis", &Input::GetJoyAxis),
                def("GetJoyButton", &Input::GetJoyButton),
                def("GetJoyHat", &Input::GetJoyHat),
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