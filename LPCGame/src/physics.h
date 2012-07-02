#ifndef PHYSICS_H
#define PHYSICS_H
#include <cmath>
#include <vector>
#include "math.h"
#include "map.h"

const int GROUND_FRICTION = 800;

/*
*	A kinematics structure, describes an object's position, velocity and acceleration
*/
struct Kinematic{
	Vector2f Pos, Vel, Accel;
};
/**
*	Describes the various speed and acceleration constants for an object
*	such as jump and horizontal acceleration and max speeds
*/
struct PhysicalConstants{
	int w, h;
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
	void UpdateState(float deltaT, Kinematic kinematic);
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
	Physics(PhysicalConstants physConstants);
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
	//this is just used for debugging
	int GetMotionState() const;
	void SetPosition(Vector2f pos);
	void SetVelocity(Vector2f vel);
	void SetAcceleration(Vector2f accel);
	void SetHorizDir(int moveDir);
	void SetVertDir(int moveDir);
	void SetPhysConstants(PhysicalConstants physConstants);
	void SetMap(CollisionMap map);

private:
	/**
	*	Updates the velocity by running the various acceleration functions
	*	@param deltaT: the elapsed time
	*/
	void UpdateVelocity(float deltaT);
	/**
	*	Apply the acceleration vector to the velocity vector, factoring in time elapsed
	*	@param deltaT: the elapsed time
	*/
	void ApplyAcceleration(float deltaT);
	/**
	*	Apply friction to the object against the direction of motion
	*	based on its status, ground or air friction will be applied
	*	@param deltaT: the elapsed time
	*/
	void ApplyFriction(float deltaT);

public:
	enum MOVE { RIGHT, LEFT, UP, DOWN, STOP };
private:
	Kinematic mKinematic;
	MotionState mMotionState;
	PhysicalConstants mPhysConstants;
	//a pointer to the active map, makes it easy to grab the tiles for collision checks
	CollisionMap mCollisionMap;
	int mHorizDir, mVertDir;
};

#endif