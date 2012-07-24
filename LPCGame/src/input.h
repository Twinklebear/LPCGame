#ifndef INPUT_H
#define INPUT_H

#include "SDL.h"
#include "gameobjectmanager.h"

//TODO: I would like to create a static wrapper around SDL's event handler
/*
*  Input: a simple wrapper around SDL's input handling system
*/
class Input{
public:
	Input();
	~Input();
	///Initialize the input manager
	static void Init();
	///Read event input
	static void PollEvent();
	//Get if a key is currently being pressed
	static bool KeyDown(char keyCode);
	//Check if the program has been quit out of
	static bool Quit();
	//Reset quit
	static void ClearQuit();
	//TODO: How should i handle mouse events? Perhaps i can register a callback function or something?
	//Trying an idea for mouse handling
	static void RegisterManager(GameObjectManager *manager);
	//Unregister the active manager
	static void RemoveManager();

private:
	static SDL_Event evt;
	static bool mQuit;
	static GameObjectManager *mManager;
	static Uint8 *mKeyStates;
};

#endif