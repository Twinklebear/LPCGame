#ifndef PHYSICS_H
#define PHYSICS_H

#include <cmath>
#include <vector>
#include "../externals/json/json.h"
#include "base.h"
#include "math.h"

const int GROUND_FRICTION = 800;

/**
*  A kinematics structure, describes an object's velocity and acceleration
*/
struct Kinematic{
	Vector2f Vel, Accel;
};
/**
*  Describes the various physical constants of an object, such
*  as max speed and acceleration
*/
struct PhysicalConstants{
	int hAccel, hSpeed;
};

/**
*  Describes the state of an object's motion
*  This isn't really used much at the motion, but will come into
*  play when showing animations for the object's actions
*/
class MotionState{
public:
	MotionState();
	~MotionState();
	/**
	*  Update the object's motion state based on its current motion
	*  @param kinematic The object's kinematic component
	*/
	void UpdateState(Kinematic kinematic);
	///Get the motion state, @see MotionState enum
	int GetMotionState() const;
	///Set the motion state
	void SetMotionstate(int state);
	///enum for describing motion states
	enum { IDLE, RUNNING };

private:
	int mState;
};

/**
*  Handles an objects physics
*/
class Physics{
public:
	Physics();
	~Physics();
	/**
	*  Update the state of the object
	*  @param deltaT The elapsed time
	*/
	void Move(float deltaT);
	/**
	*  Return the velocity distance to move in the elapsed time
	*  @param deltaT The elapsed time
	*/
	Vector2f GetFrameMove(float deltaT);
	///Getters
	Vector2f GetPosition() const;
	Vector2f GetVelocity() const;
	Vector2f GetAcceleration() const;
	Rectf Box() const;
	int GetMotionState() const;
	///Setters
	void SetPosition(Vector2f pos);
	void SetVelocity(Vector2f vel);
	void SetAcceleration(Vector2f accel);
	///Set the horizontal move direction @see Math enum
	void SetHorizDir(int moveDir);
	///Set the vertical move direction @see Math enum
	void SetVertDir(int moveDir);
	void SetPhysConstants(PhysicalConstants physConstants);
	void SetBox(Rectf box);
	void SetMap(CollisionMap map);
	/**
	*  Save the physical properties of the object to a Json::Value
	*  @return Json::Value containing the object's physical properties
	*/
	Json::Value Save();
	/**
	*  Load the object's physical properties from a Json::Value
	*  @param val The Json::Value containing the properties to load
	*/
	void Load(Json::Value val);

private:
	/**
	*  Updates the velocity by running the various acceleration functions
	*  @param deltaT The elapsed time
	*/
	void UpdateVelocity(float deltaT);
	/**
	* Apply the acceleration vector to the velocity vector
	*/
	void ApplyAcceleration();
	/**
	*  Apply friction to the object against the direction of motion
	*  based on its status, ground or air friction will be applied
	*/
	void ApplyFriction();
	/**
	*  Check for collision of the entity box with the local collision map
	*  @param box the entity's box, note that this may be a temp box for testing collision
	*  @return bool True if collision, False otherwise
	*/
	bool CheckCollision(Rectf box);

public:
	///Move enum, at the moment just has one for Stop as Math enum is used for dir @see Math
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