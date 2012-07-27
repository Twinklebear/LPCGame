#ifndef STATEMANAGER_H
#define STATEMANAGER_H

#include <vector>
#include <string>
#include <memory>
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
	*  Start the first state, first state must have name intro
	*/
	static void InitIntro();
	//TODO: Need functions for selecting the active state and running it
	/*  
	*  TODO: How will i save and load states? Perhaps i will serialize the state before
	*  before i delete it, and then when I load the state, I'll pass the name of the state
	*  I want to load which will bring up the associated file
	*/
	/*
	*  Set a state active based on its name
	*  @param name: The name of the state to set active
	*/
	static void SetActiveState(std::string name);
	/*
	*  Load a from file by its name
	*  @param name: The state name to load for the state, state and file names are same
	*  @returns: True if state was successfully loaded
	*/
	static bool LoadState(std::string name);
	/*
	*  Save a state to a data file corresponding to its name
	*  @param name: The state name to save, state and file names are the same
	*/
	static void SaveState(std::string name);

private:
	/*
	*  Set the mActiveState as the State pointer passed
	*  @param state: The state to run
	*/
	static void SetState(State* state);

private:
	static std::shared_ptr<State> mActiveState;
	const static std::string mStatesDir;
};

#endif