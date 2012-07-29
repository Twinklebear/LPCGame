#ifndef STATE_H
#define STATE_H

#include <string>
#include <memory>
#include "json/json.h"
#include "gameobjectmanager.h"
#include "camera.h"

/**
*  The base class for our state machine, provides functions
*  for initializing state, running the state and memory clean-up
*/
class State{
public:
	State();
	virtual ~State();
	/**
	*  Run the state
	*  @return The next state to run, returning quit exits program
	*/
	virtual std::string Run() = 0;
	/**
	*  Set the exit code to return from Run and set exit to true
	*  @param val The exit code to return from Run
	*  @see Run
	*/
	void SetExit(std::string val);
	///Set exit to false
	void UnsetExit();
	/**
	*  Save the state data so that it can be loaded later
	*  @return Json::Value containing the state data
	*/
	virtual Json::Value Save() = 0;
	/**
	*  Load the state from a Json::Value
	*  @param val The Json::Value to load from
	*/
	virtual void Load(Json::Value val) = 0;
	/**
	*  Set the state's name
	*  @param name The name to set
	*/
	void SetName(std::string name);
	///Get the state's name
	std::string Name();

protected:
	///Initialize state memory
	virtual void Init() = 0;
	///Free the memory used by the state
	virtual void Free() = 0;

protected:
	std::shared_ptr<GameObjectManager> mManager;
	std::shared_ptr<Camera> mCamera;
	Rectf mSceneBox;
	std::string mName;
	bool mExit;
	std::string mExitCode;
};


#endif