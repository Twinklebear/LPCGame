#ifndef INPUT_H
#define INPUT_H

#include "SDL.h"

//TODO: I would like to create a static wrapper around SDL's event handler
/*
*  Input: a simple wrapper around SDL's input handling system
*/
class Input{
public:
	Input();
	~Input();
	///Read event input
	static void PollEvent();
	static bool KeyDown(char keyCode);
	static bool Quit();

private:
	static SDL_Event event;
	static bool fDown;
	static bool mQuit;
};

#endif