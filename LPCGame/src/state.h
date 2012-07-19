#ifndef STATE_H
#define STATE_H

#include <string>
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
	/*
	*  Serialize the state data so that it can be loaded later
	*  @returns: The serialized data in string form
	*/
	virtual std::string Serialize() = 0;
	//Setters & Getters
	virtual void SetId(int id);
	virtual int Id();
	virtual void SetName(std::string name);
	virtual std::string Name();

protected:
	GameObjectManager *mManager;
	int mId;
	std::string mName;
};


#endif