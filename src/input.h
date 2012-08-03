#ifndef INPUT_H
#define INPUT_H

#include <memory>
#include "SDL.h"
#include "gameobjectmanager.h"
#include "uiobjectmanager.h"

///Input handler wrapper
/**
*  A simple wrapper around SDL's input handling system
*/
class Input{
public:
	Input();
	~Input();
	///Initialize the input manager
	static void Init();
	///Free the active managers
	static void FreeManagers();
	///Read event input
	static void PollEvent();
	/**
	*  Check if a key is being pressed down
	*  TODO: I need a way to handle special keys, perhaps a version of this
	*  that takes the SDL_SCANCODE?
	*  @param keyCode The char of the key to check, ex: 'a'
	*  @return T if key is down
	*/
	static bool KeyDown(char keyCode);
	/**
	*  Check if a key is being pressed down
	*  @param keyCode The SDL_SCANCODE of the key
	*  @return T if key is down
	*/
	static bool KeyDown(int keyCode);
	/**
	*  
	*/
	///Check if the mouse was clicked
	static bool MouseClick();
	///Check if the mouse moved
	static bool MouseMotion();
	///Check if the program has been quit out of
	static bool Quit();
	///Reset quit
	static void ClearQuit();
	///Clear the keystates
	static void ClearKeys();
	/**
	*  Register the gameobject manager with the input handler so 
	*  that we can pass it mouse events easily
	*  @param manager The gameobject manager to send events too
	*/
	static void RegisterManager(std::shared_ptr<GameObjectManager> manager);
	/**
	*  Register the ui object manager with the input handler
	*  @param manager The ui object manager
	*/
	static void RegisterManager(std::shared_ptr<UiObjectManager> manager);

private:
	static SDL_Event evt;
	static bool mQuit;//, mMouseClick, mMouseMove;
	static std::weak_ptr<GameObjectManager> mGameObjectManager;
	static std::weak_ptr<UiObjectManager> mUiObjectManager;
	static Uint8 *mKeyStates;
	//How would i determine if the event was recent or not?
	//ie. if i use these to track the event, after the event happened
	//they need to be reset along with the bool values
	//static SDL_MouseButtonEvent mButtonEvt;
	//static SDL_MouseMotionEvent mMotionEvt;
};

#endif