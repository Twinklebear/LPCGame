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
	*  Start the first state, first state must have name intro
	*/
	static void InitIntro();
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
	/*  
	*  TODO: How will i save and load states? Perhaps i will serialize the state before
	*  before i delete it, and then when I load the state, I'll pass the name of the state
	*  I want to load which will bring up the associated file
	*/
	/*
	*  Set a state active based on its Id number
	*  @param id: The state id (index) to set active
	*/
	static void SetActiveState(int id);
	/*
	*  Load a from file by its name
	*  @param name: The state name to load for the state, state and file names are same
	*/
	static void LoadState(std::string name);
	/*
	*  Save a state to a data file corresponding to its name
	*  @param name: The state name to save, state and file names are the same
	*/
	static void SaveState(std::string name);

private:
	static std::vector<State*> mStates;
	static int mActiveID;
};

#endif