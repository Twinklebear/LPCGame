#include "math.h"
#include "physics.h"
#include <iostream>

MotionState::MotionState(){
	mState = IDLE;
}
MotionState::~MotionState(){
}
void MotionState::UpdateState(Kinematic kinematic){
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

	//TODO: Need to set velocity to small value in direction of motion if colliding with wall but moving away from it
	if (CheckCollision(Rectf(testPos.x, mKinematic.Pos.y, mPhysConstants.w, mPhysConstants.h))){
	}
	else 
		mKinematic.Pos.x = testPos.x;

	if (CheckCollision(Rectf(mKinematic.Pos.x, testPos.y, mPhysConstants.w, mPhysConstants.h))){
	}
	else
		mKinematic.Pos.y = testPos.y;

	mMotionState.UpdateState(mKinematic);
}
void Physics::UpdateVelocity(float deltaT){
	ApplyAcceleration();
	ApplyFriction();
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
void Physics::ApplyAcceleration(){
	if (mHorizDir == Math::RIGHT)
		mKinematic.Accel.x = mPhysConstants.hAccel;
	else if (mHorizDir == Math::LEFT)
		mKinematic.Accel.x = -mPhysConstants.hAccel;
	else
		mKinematic.Accel.x = 0;
	if (mVertDir == Math::UP)
		mKinematic.Accel.y = -mPhysConstants.hAccel;
	else if (mVertDir == Math::DOWN)
		mKinematic.Accel.y = mPhysConstants.hAccel;
	else
		mKinematic.Accel.y = 0;
}
void Physics::ApplyFriction(){
	if (mHorizDir == MOVE::STOP && mKinematic.Vel.x != 0.0){
		mKinematic.Accel.x += GROUND_FRICTION * (-mKinematic.Vel.x / abs(mKinematic.Vel.x));
	}
	if (mVertDir == MOVE::STOP && mKinematic.Vel.y != 0.0){
		mKinematic.Accel.y += GROUND_FRICTION * (-mKinematic.Vel.y / abs(mKinematic.Vel.y));
	}
}
bool Physics::CheckCollision(Rectf box){
	for (Recti i : mCollisionMap){
		if (Math::CheckCollision(box, i)){
			/*
			*	TODO: Need a way to lock out the direction of motion that created the collision until 
			*	player moves in opposite direction
			//if trying to move in direction of collision set vel to 0
			if (mHorizDir != MOVE::STOP && Math::RectNearRect(box, i, 1) == mHorizDir){
				mHorizDir = MOVE::STOP;
				mKinematic.Vel.x = 0;
			}
			if (mVertDir != MOVE::STOP && Math::RectNearRect(box, i, 1) == mVertDir){
				mVertDir = MOVE::STOP;
				mKinematic.Vel.y = 0;
			}
			*/
			return true;
		}
	}
	return false;
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
	if (moveDir == Math::UP || moveDir == Math::DOWN)
		throw std::runtime_error("Bad Horizontal Direction");
	mHorizDir = moveDir;
}
void Physics::SetVertDir(int moveDir){
	if (moveDir == Math::LEFT || moveDir == Math::RIGHT)
		throw std::runtime_error("Bad Vertical Direction");
	mVertDir = moveDir;
}
void Physics::SetPhysConstants(PhysicalConstants physConstants){
	mPhysConstants = physConstants;
}
void Physics::SetMap(CollisionMap map){
	mCollisionMap = map;
}