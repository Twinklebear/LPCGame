#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "state.h"
#include "timer.h"
#include "map.h"

/*
*  A simple state to run the game
*  Todo: how should i handle multiple levels? All in gamestate?
*/
class GameState : public State{
public:
	GameState();
	~GameState();
	//Initialize state memory
	void Init();
	//Run the state
	void Run();
	//Free the memory used by the state
	void Free();
	/*
	*  Serialize the state data so that it can be loaded later
	*  @returns: The serialized data in string form
	*/
	std::string Serialize();

private:
	Map *mMap;
	Timer mDelta;
};

#endif