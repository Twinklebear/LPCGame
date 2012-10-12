#ifndef MOTIONSTATE_H
#define MOTIONSTATE_H

#include <luabind/luabind.hpp>
#include "vectors.h"

///Struct to track velocity and acceleration
/**
*  A kinematics structure, describes an object's velocity and acceleration
*/
struct Kinematic {
	Vector2f Vel, Accel;
};

///Track object's various physical constants
/**
*  Describes the various physical constants of an object, such
*  as max speed and acceleration
*/
struct PhysicalConstants {
	int hAccel, hSpeed;
};

///For tracking an object's motion state
/**
*  Describes the state of an object's motion
*  This isn't really used much at the motion, but will come into
*  play when showing animations for the object's actions
*/
class MotionState {
public:
	MotionState();
	~MotionState();
	/**
	*  Update the object's motion state based on its current motion
	*  @param kinematic The object's kinematic component
	*/
	void UpdateState(Kinematic kinematic);
	///Get the motion state, @see MotionState enum
	int State() const;
	///Set the motion state
	void SetMotionState(int state);
	///enum for describing motion states
	enum { IDLE, RUNNING };
	/**
	*  Register the MotionState class with the lua state
	*  TODO: Is this necessary? Shouldn't this sort of physics be done by the user?
	*  @param l The lua_State to register the module with
	*/
	static int RegisterLua(lua_State *l);

private:
	int mState;
};

#endif