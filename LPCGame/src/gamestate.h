#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "json/json.h"
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
	//Run the state
	std::string Run();
	/*
	*  Write the state data to a Json Value and return it so that
	*  it can be saved and loaded later
	*/
	Json::Value Save();
	/*
	*  Load the state data from a json value
	*  @param value: the Json::Value containing the data to load
	*/
	void Load(Json::Value value);

protected:
	//Initialize state memory
	void Init();
	//Free state memory
	void Free();

private:
	Map *mMap;
	Timer mDelta;
};

#endif