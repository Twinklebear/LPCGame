#include <luabind/luabind.hpp>
#include "vectors.h"
#include "motionstate.h"

MotionState::MotionState(){
	mState = IDLE;
}
MotionState::~MotionState(){
}
void MotionState::UpdateState(Kinematic kinematic){
	//update state based on current motion
	if (abs(kinematic.Vel.x) > 0.05 || abs(kinematic.Vel.y) >= 0.05)
		mState = RUNNING;
	else
		mState = IDLE;
}
int MotionState::GetMotionState() const{
	return mState;
}
void MotionState::SetMotionstate(int state){
	mState = state;
}
void MotionState::RegisterLua(lua_State *l){

}