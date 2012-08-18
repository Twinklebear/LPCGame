#ifndef STATE_H
#define STATE_H

#include <string>
#include <memory>
#include <atomic>
#include <condition_variable>
#include "../externals/json/json.h"
#include "entitymanager.h"
#include "camera.h"

///Base class for states
/**
*  The base class for our state machine, provides functions
*  for initializing state, running the state and memory clean-up
*/
class State{
public:
	State();
	virtual ~State();
	/**
	*  Run the state, this function becomes the main Input thread
	*  after starting up the physics and rendering threads
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
	virtual Json::Value Save();
	/**
	*  Load the state from a Json::Value
	*  @param val The Json::Value to load from
	*/
	virtual void Load(Json::Value val);
	/**
	*  Set the state's name
	*  @param name The name to set
	*/
	void SetName(std::string name);
	///Get the state's name
	std::string Name();

protected:
	/**
	*  The state's rendering thread, takes care of drawing all objects
	*  and providing framerate limiting condition variable notifications
	*  to all other threads
	*  NOT USED AT THE MOMENT
	*/
	//virtual void RenderThread() = 0;
	/**
	*  The state's physics thread, takes care of updating and moving
	*  all objects and managing physics between the objects
	*  NOT USED AT THE MOMENT
	*/
	//virtual void PhysicsThread() = 0;
	///Initialize state memory
	virtual void Init() = 0;
	///Free the memory used by the state
	virtual void Free() = 0;

protected:
	std::shared_ptr<EntityManager> mManager;
	std::shared_ptr<Camera> mCamera;
	std::string mName;
	//Should this be atomic?
	bool mExit;
	std::string mExitCode;
	///Condition variable and double check bool variable
	//std::condition_variable mCondVar;
	//Do i need this?
	//std::atomic<bool> mCondBool;
};


#endif