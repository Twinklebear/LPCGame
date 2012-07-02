#include "physics.h"

MotionState::MotionState(){
	mState = IDLE;
}
MotionState::~MotionState(){
}
void MotionState::UpdateState(float deltaT, Kinematic kinematic){
	//update state based on current motion
	if (abs(kinematic.Vel.x) > 0.0 || abs(kinematic.Vel.y) >= 0.0)
		mState = RUNNING;
	else if (kinematic.Vel.x == 0.0 && kinematic.Vel.y == 0.0)
		mState = IDLE;
}
int MotionState::GetMotionState() const{
	return mState;
}
void MotionState::SetMotionstate(int state){
	mState = state;
}

Physics::Physics(){
	//init kinematic values
	mKinematic.Pos		= Vector2f(0, 0);
	mKinematic.Vel		= Vector2f(0, 0);
	mKinematic.Accel	= Vector2f(0, 0);
	//init constants
	mPhysConstants.w		= 0;
	mPhysConstants.h		= 0;
	mPhysConstants.hAccel	= 0;
	mPhysConstants.hSpeed	= 0;
	mHorizDir = MOVE::STOP;
	mVertDir  = MOVE::STOP;
}
Physics::Physics(PhysicalConstants physConstants){
	//init kinematic values
	mKinematic.Pos		= Vector2f(0, 0);
	mKinematic.Vel		= Vector2f(0, 0);
	mKinematic.Accel	= Vector2f(0, 0);
	//set constants
	mPhysConstants = physConstants;
	mHorizDir = MOVE::STOP;
	mVertDir  = MOVE::STOP;
}
Physics::~Physics(){
}
void Physics::Move(float deltaT){
	//Update the velocity
	UpdateVelocity(deltaT);
	//test if the move is ok before applying changes
	Vector2f testPos;
	testPos = mKinematic.Pos + (mKinematic.Vel * deltaT);

	//TODO: Add collision checking before allowing the player move
	//Collision checking should be done before accepting the change
	//collision checks must be seperate along each axis

	mKinematic.Pos.x = testPos.x;
	mKinematic.Pos.y = testPos.y;

	mMotionState.UpdateState(deltaT, mKinematic);
}
void Physics::UpdateVelocity(float deltaT){
	//I think the issue is that setting the velocity without checking the move is what is causing the problem
	ApplyAcceleration(deltaT);
	ApplyFriction(deltaT);
	//if applying the friction would cause the velocity to flip signs, set velocity to 0
	if (mHorizDir == MOVE::STOP && ((mKinematic.Vel.x + mKinematic.Accel.x * deltaT > 0.0 && mKinematic.Vel.x < 0.0)
		|| (mKinematic.Vel.x + mKinematic.Accel.x * deltaT < 0.0 && mKinematic.Vel.x > 0.0)))
			mKinematic.Vel.x = 0.0;
	else 
		mKinematic.Vel.x += mKinematic.Accel.x * deltaT;
	//same for y
	if (mVertDir == MOVE::STOP && ((mKinematic.Vel.y + mKinematic.Accel.y * deltaT > 0.0 && mKinematic.Vel.y < 0.0)
		|| (mKinematic.Vel.y + mKinematic.Accel.y * deltaT < 0.0 && mKinematic.Vel.y > 0.0)))
			mKinematic.Vel.y = 0.0;
	else 
		mKinematic.Vel.y += mKinematic.Accel.y * deltaT;

	//limit velocity
	if ((mKinematic.Vel.x > mPhysConstants.hSpeed) || (mKinematic.Vel.x < -mPhysConstants.hSpeed))
		mKinematic.Vel.x = mPhysConstants.hSpeed * (mKinematic.Vel.x / abs(mKinematic.Vel.x));
	//for y as well
	if ((mKinematic.Vel.y > mPhysConstants.hSpeed) || (mKinematic.Vel.y < -mPhysConstants.hSpeed))
		mKinematic.Vel.y = mPhysConstants.hSpeed * (mKinematic.Vel.y / abs(mKinematic.Vel.y));
}
void Physics::ApplyAcceleration(float deltaT){
	if (mHorizDir == MOVE::RIGHT)
		mKinematic.Accel.x = mPhysConstants.hAccel;
	else if (mHorizDir == MOVE::LEFT)
		mKinematic.Accel.x = -mPhysConstants.hAccel;
	else
		mKinematic.Accel.x = 0;
	if (mVertDir == MOVE::UP)
		mKinematic.Accel.y = -mPhysConstants.hAccel;
	else if (mVertDir == MOVE::DOWN)
		mKinematic.Accel.y = mPhysConstants.hAccel;
	else
		mKinematic.Accel.y = 0;
}
void Physics::ApplyFriction(float deltaT){
	if (mHorizDir == MOVE::STOP && mKinematic.Vel.x != 0.0){
		mKinematic.Accel.x += GROUND_FRICTION * (-mKinematic.Vel.x / abs(mKinematic.Vel.x));
	}
	if (mVertDir == MOVE::STOP && mKinematic.Vel.y != 0.0){
		mKinematic.Accel.y += GROUND_FRICTION * (-mKinematic.Vel.y / abs(mKinematic.Vel.y));
	}
}
Vector2f Physics::GetFrameMove(float deltaT){
	return (mKinematic.Vel * deltaT);
}
Vector2f Physics::GetPosition() const{
	return mKinematic.Pos;
}
Vector2f Physics::GetVelocity() const{
	return mKinematic.Vel;
}
Vector2f Physics::GetAcceleration() const{
	return mKinematic.Accel;
}
int Physics::GetMotionState() const{
	return mMotionState.GetMotionState();
}
void Physics::SetPosition(Vector2f pos){
	mKinematic.Pos = pos;
}
void Physics::SetVelocity(Vector2f vel){
	mKinematic.Vel = vel;
}
void Physics::SetAcceleration(Vector2f accel){
	mKinematic.Accel = accel;
}
void Physics::SetHorizDir(int moveDir){
	if (moveDir == MOVE::UP || moveDir == MOVE::DOWN)
		throw std::runtime_error("Bad Horizontal Direction");
	mHorizDir = moveDir;
}
void Physics::SetVertDir(int moveDir){
	if (moveDir == MOVE::LEFT || moveDir == MOVE::RIGHT)
		throw std::runtime_error("Bad Vertical Direction");
	mVertDir = moveDir;
}
void Physics::SetPhysConstants(PhysicalConstants physConstants){
	mPhysConstants = physConstants;
}
void Physics::SetMap(const CollisionMap &map){
	mCollisionMap = map;
}