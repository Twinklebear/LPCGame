#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <memory>
#include "../externals/json/json.h"
#include "state.h"
#include "timer.h"
#include "map.h"

/**
*  A simple game state that can run a level of the game
*/
class GameState : public State{
public:
	GameState();
	~GameState();
	/**
	*  Run the state
	*  @return The next state to run, returning quit exits program
	*/
	std::string Run();
	/**
	*  Write the state data to a Json Value and return it so that
	*  it can be saved and loaded later
	*  @return Json::Value containing the state's save data
	*/
	Json::Value Save();
	/**
	*  Load the state data from a json value
	*  @param val The Json::Value containing the data to load
	*/
	void Load(Json::Value val);

protected:
	///Initialize state memory
	void Init();
	///Free state memory
	void Free();

private:
	std::shared_ptr<Map> mMap;
	Timer mDelta;
};

#endif