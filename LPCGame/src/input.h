#include "SDL.h"

//TODO: I would like to create a static wrapper around SDL's event handler
/*
*  Input: a simple wrapper around SDL's input handling system
*/
class Input{
public:
	Input();
	~Input();

private:
	SDL_Event event;
};