#ifndef STATEMANAGER_H
#define STATEMANAGER_H

#include <vector>
#include "state.h"
#include "gamestate.h"
#include "menustate.h"

/*
*  A wrapper class designed to handle interactions between the 
*  various states
*/
class StateManager{
public:
	/*
	*  Register a state with the manager, each state is assigned an id number
	*  corresponding to its index in the vector
	*  @param state: The state to register
	*/
	static void Register(State *state);
	/*
	*  Get a state's Id number based on its name
	*  @param name: The state's name
	*  @returns: The state's ID number
	*/
	static int IdFromName(std::string name);
	//TODO: Need functions for selecting the active state and running it

private:
	static std::vector<State> mStates;
};

#endif