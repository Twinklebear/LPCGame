#ifndef STATE_H
#define STATE_H

#include <string>
#include <memory>
#include "json/json.h"
#include "gameobjectmanager.h"
#include "camera.h"

/*
*  The base class for our state machine, provides functions
*  for initializing state, running the state and memory clean-up
*/
class State{
public:
	State();
	virtual ~State();
	//Run the state
	virtual std::string Run() = 0;
	//Set the exit code for Run, and set mExit to true
	void SetExit(std::string val);
	//Reset the exit values to default
	void UnsetExit();
	/*
	*  Save the state data so that it can be loaded later
	*  @returns: Json::Value containing the state data
	*/
	virtual Json::Value Save() = 0;
	/*
	*  Load the state from a Json::Value
	*  @param value: The Json::Value to load from
	*/
	virtual void Load(Json::Value) = 0;
	//Setters & Getters
	void SetName(std::string name);
	std::string Name();

protected:
	//Initialize state memory
	virtual void Init() = 0;
	//Free the memory used by the state
	virtual void Free() = 0;

protected:
	std::shared_ptr<GameObjectManager> mManager;
	std::shared_ptr<Camera> mCamera;
	std::string mName;
	bool mExit;
	std::string mExitCode;
};


#endif