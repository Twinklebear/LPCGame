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
	mBox.Set(0, 0, 0, 0);
	mKinematic.Vel	 = Vector2f(0, 0);
	mKinematic.Accel = Vector2f(0, 0);
	mPhysConstants.hAccel	= 0;
	mPhysConstants.hSpeed	= 0;
	mHorizDir = MOVE::STOP;
	mVertDir  = MOVE::STOP;
}
Physics::Physics(PhysicalConstants physConstants, Rectf box){
	//init kinematic values
	mKinematic.Vel	 = Vector2f(0, 0);
	mKinematic.Accel = Vector2f(0, 0);
	mBox = box;
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
	testPos = mBox.Pos() + (mKinematic.Vel * deltaT);

	//TODO: Need to set velocity to small value in direction of motion if colliding with wall but moving away from it
	//x axis collision checks
	if (CheckCollision(Rectf(testPos.x, mBox.Y(), mBox.W(), mBox.H()))){
	}
	else 
		mBox.Set(testPos.x, mBox.Y());
	//y axis collision checks
	if (CheckCollision(Rectf(mBox.X(), testPos.y, mBox.W(), mBox.H()))){
	}
	else
		mBox.Set(mBox.X(), testPos.y);

	std::cout << "---------END UPDATE-------\n\n";

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
	//We get rid of the benefits of early out to instead be able to check all tiles
	//we're colliding with for a collision direction, in the hopes that one of them should almost
	//certainly return a valid direction within our tolerance
	//TODO: Can i have my cake and eat it too? early out + direction resolution?
	bool colliding = false;
	for (Recti i : mCollisionMap){
		if (Math::CheckCollision(box, i)){
			std::cout << "COLLISION" << std::endl;
			/*
			*	TODO: Need a way to lock out the direction of motion that created the collision until 
			*	player moves in opposite direction
			*/
			//if trying to move in direction of collision set vel to 0
			int colDir = Math::RectNearRect(box, i, 15);
			std::cout << "colliding with box on side: " << colDir << std::endl;
			if (mHorizDir != MOVE::STOP && colDir != -1){
				//std::cout << "Locking x move dir" << std::endl;
				mHorizDir = MOVE::STOP;
				mKinematic.Vel.x = 0;
			}
			if (mVertDir != MOVE::STOP && colDir != -1){
				mVertDir = MOVE::STOP;
				mKinematic.Vel.y = 0;
			}
			colliding = true;
		}
	}
	return colliding;
}
Vector2f Physics::GetFrameMove(float deltaT){
	return (mKinematic.Vel * deltaT);
}
Vector2f Physics::GetPosition() const{
	return mBox.Pos();
}
Vector2f Physics::GetVelocity() const{
	return mKinematic.Vel;
}
Vector2f Physics::GetAcceleration() const{
	return mKinematic.Accel;
}
Rectf Physics::Box() const{
	return mBox;
}
int Physics::GetMotionState() const{
	return mMotionState.GetMotionState();
}
void Physics::SetPosition(Vector2f pos){
	mBox.Set(pos);
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
void Physics::SetBox(Rectf box){
	mBox = box;
}
void Physics::SetMap(CollisionMap map){
	mCollisionMap = map;
}