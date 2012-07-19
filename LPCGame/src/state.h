#ifndef STATE_H
#define STATE_H

#include "gameobjectmanager.h"

/*
*  The base class for our state machine, provides functions
*  for initializing state, running the state and memory clean-up
*/
class State{
public:
	State();
	virtual ~State();
	//Initialize state memory
	virtual void Init() = 0;
	//Run the state
	virtual void Run() = 0;
	//Free the memory used by the state
	virtual void Free() = 0;

private:
	GameObjectManager *manager;
};


#endif