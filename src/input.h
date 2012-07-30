#ifndef INPUT_H
#define INPUT_H

#include <memory>
#include "SDL.h"
#include "gameobjectmanager.h"

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
	///Read event input
	static void PollEvent();
	/**
	*  Check if a key is being pressed down
	*  TODO: I need a way to handle special keys, perhaps a version of this
	*  that takes the SDL_SCANCODE?
	*  @param keyCode The char of the key to check, ex: 'a'
	*  @return T/F whether key is down or not
	*/
	static bool KeyDown(char keyCode);
	///Check if the program has been quit out of
	static bool Quit();
	///Reset quit
	static void ClearQuit();
	/**
	*  Register the gameobject manager with the input handler so 
	*  that we can pass it mouse events easily
	*  @param manager The gameobject manager to send events too
	*/
	static void RegisterManager(std::shared_ptr<GameObjectManager> manager);
	///Unregister the active manager
	static void RemoveManager();

private:
	static SDL_Event evt;
	static bool mQuit;
	static std::weak_ptr<GameObjectManager> mManager;
	static Uint8 *mKeyStates;
};

#endif