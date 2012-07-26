#ifndef PHYSICS_H
#define PHYSICS_H

#include <cmath>
#include <vector>
#include "json/json.h"
#include "math.h"
#include "map.h"

const int GROUND_FRICTION = 800;

/*
*	A kinematics structure, describes an object's position, velocity and acceleration
*/
struct Kinematic{
	Vector2f Vel, Accel;
};
/**
*	Describes the various speed and acceleration constants for an object
*	such as jump and horizontal acceleration and max speeds
*/
struct PhysicalConstants{
	int hAccel, hSpeed;
};
/*
*	Describes the state of an object's motion
*/
class MotionState{
public:
	MotionState();
	~MotionState();
	///Update the motion state based on current action
	void UpdateState(Kinematic kinematic);
	///Setters & getters
	int GetMotionState() const;
	void SetMotionstate(int state);
	///enum for describing motion state
	enum { IDLE, RUNNING };

private:
	int mState;
};

/*
*	Handles general physics functions & calculations
*/
class Physics{
public:
	Physics();
	Physics(PhysicalConstants physConstants, Rectf box);
	~Physics();
	/**
	*	Update the state of the object
	*	@param deltaT: the elapsed time
	*/
	void Move(float deltaT);
	/**
	*	Return the velocity distance to move in the elapsed time
	*	@param deltaT: the elapsed time
	*/
	Vector2f GetFrameMove(float deltaT);
	///Setters & getters
	Vector2f GetPosition() const;
	Vector2f GetVelocity() const;
	Vector2f GetAcceleration() const;
	Rectf Box() const;
	//this is just used for debugging
	int GetMotionState() const;
	void SetPosition(Vector2f pos);
	void SetVelocity(Vector2f vel);
	void SetAcceleration(Vector2f accel);
	void SetHorizDir(int moveDir);
	void SetVertDir(int moveDir);
	void SetPhysConstants(PhysicalConstants physConstants);
	void SetBox(Rectf box);
	void SetMap(CollisionMap map);
	/*
	*  Save the physical properties of the object to a Json::Value
	*  @returns: The Json::Value containing the object's physical properties
	*/
	Json::Value Save();
	/*
	*  Load the object's physical properties from a Json::Value
	*  @param val: The Json::Value containing the properties to load
	*/
	void Load(Json::Value val);

private:
	/**
	*	Updates the velocity by running the various acceleration functions
	*	@param deltaT: the elapsed time
	*/
	void UpdateVelocity(float deltaT);
	/**
	*	Apply the acceleration vector to the velocity vector
	*/
	void ApplyAcceleration();
	/**
	*	Apply friction to the object against the direction of motion
	*	based on its status, ground or air friction will be applied
	*/
	void ApplyFriction();
	/**
	*	Check for collision of the entity box with the local collision map
	*	@param box: the entity's box
	*	@return bool True if collision, False otherwise
	*/
	bool CheckCollision(Rectf box);

public:
	enum MOVE { STOP = -1};
private:
	Kinematic mKinematic;
	MotionState mMotionState;
	PhysicalConstants mPhysConstants;
	Rectf mBox;
	CollisionMap mCollisionMap;
	int mHorizDir, mVertDir;
};

#endif