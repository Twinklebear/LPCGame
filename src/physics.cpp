#include <luabind/luabind.hpp>
#include "../externals/json/json.h"
#include "math.h"
#include "motionstate.h"
#include "debug.h"
#include "physics.h"

Physics::Physics(){
	mKinematic.Vel	 = Vector2f(0, 0);
	mKinematic.Accel = Vector2f(0, 0);
	mHorizDir = MOVE::STOP;
	mVertDir  = MOVE::STOP;
    mDir = Vector2f(0, 0);
}
Physics::~Physics(){}
void Physics::Move(float deltaT){
	//Update the velocity
	UpdateVelocity(deltaT);
	//test if the move is ok before applying changes
	Vector2f testPos;
	testPos = mBox.Pos() + (mKinematic.Vel * deltaT);

	//Clamp the test position x & y
	//TODO: Change these clamp ranges to be the map range, ie. map.x min map.x + map.w max
	//map.y min map.y + map.h max
	testPos.x = Math::Clamp(testPos.x, 0.0, 320.0);
	testPos.y = Math::Clamp(testPos.y, 0.0, 320.0);

	//x axis collision checks
	if (CheckCollision(Rectf(testPos.x, mBox.Y(), mBox.W(), mBox.H()))){
        //Send on collision event?
	}
	else 
		mBox.Set(testPos.x, mBox.Y());
	//y axis collision checks
	if (CheckCollision(Rectf(mBox.X(), testPos.y, mBox.W(), mBox.H()))){
        //Send on collision event?
	}
	else
		mBox.Set(mBox.X(), testPos.y);

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
    mKinematic.Accel = mDir * mPhysConstants.hAccel;
    /*
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
    */
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
	//We wait to exit the loop until we've found the collision direction and
	//checked it against our movement direction to set v to 0 if moving in direction of 
	//the collision
	bool colliding = false;
	for (Recti i : mCollisionMap){
		if (Math::CheckCollision(box, i)){
			colliding = true;
			//Check collision direction against movement directions
			int colDir = Math::RectNearRect(box, i, 15);
			if (mHorizDir == colDir){
				mKinematic.Vel.x = 0;
				return colliding;
			}
			if (mVertDir == colDir){
				mKinematic.Vel.y = 0;
				return colliding;
			}
		}
	}
	return colliding;
}
Vector2f Physics::Position() const{
	return mBox.Pos();
}
Vector2f Physics::Velocity() const{
	return mKinematic.Vel;
}
Vector2f Physics::Acceleration() const{
	return mKinematic.Accel;
}
Rectf Physics::Box() const{
	return mBox;
}
int Physics::State() const{
	return mMotionState.State();
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
		Debug::Log("Bad Horizontal Direction");
	mHorizDir = moveDir;
    if (moveDir == Math::LEFT)
        SetDirection(Vector2f(-1, mDir.y));
    else if (moveDir == Math::RIGHT)
        SetDirection(Vector2f(1, mDir.y));
    else if (moveDir == MOVE::STOP)
        SetDirection(Vector2f(0, mDir.y));
}
void Physics::SetVertDir(int moveDir){
	if (moveDir == Math::LEFT || moveDir == Math::RIGHT)
		Debug::Log("Bad Vertical Direction");
	mVertDir = moveDir;
    if (moveDir == Math::UP)
        SetDirection(Vector2f(mDir.x, -1));
    else if (moveDir == Math::DOWN)
        SetDirection(Vector2f(mDir.x, 1));
    else if (moveDir == MOVE::STOP)
        SetDirection(Vector2f(mDir.x, 0));
}
void Physics::SetDirection(Vector2f v){
    mDir = Math::Normalize(v);
    //Backwards compatiability garbage
    if (mDir.x > 0)
        mHorizDir = Math::RIGHT;
    else if (mDir.x < 0)
        mHorizDir = Math::LEFT;
    else
        mHorizDir = MOVE::STOP;
    if (mDir.y > 0)
        mVertDir = Math::DOWN;
    else if (mDir.y < 0)
        mVertDir = Math::UP;
    else
        mVertDir = MOVE::STOP;
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
Json::Value Physics::Save() const {
	//Save the object's physical constants and box
	Json::Value val;
	val["box"] 	  = mBox.Save();
	val["hSpeed"] = mPhysConstants.hSpeed;
	val["hAccel"] = mPhysConstants.hAccel;
	return val;
}
void Physics::Load(Json::Value val){
	mBox.Load(val["box"]);
	mPhysConstants.hAccel = val["hAccel"].asInt();
	mPhysConstants.hSpeed = val["hSpeed"].asInt();

	//Setup motion values
	mKinematic.Vel	 = Vector2f(0, 0);
	mKinematic.Accel = Vector2f(0, 0);
	mHorizDir = MOVE::STOP;
	mVertDir  = MOVE::STOP;
}
int Physics::RegisterLua(lua_State *l){
	using namespace luabind;

	module(l, "LPC")[
		class_<Physics>("Physics")
			.def(constructor<>())
			.def("Move", &Physics::Move)
			.def("Position", &Physics::Position)
			.def("Velocity", &Physics::Velocity)
			.def("Acceleration", &Physics::Acceleration)
			.def("Box", &Physics::Box)
			.def("State", &Physics::State)
			.def("SetPosition", &Physics::SetPosition)
			.def("SetVelocity", &Physics::SetVelocity)
			.def("SetAcceleration", &Physics::SetAcceleration)
			.def("SetHorizDir", &Physics::SetHorizDir)
			.def("SetVertDir", &Physics::SetVertDir)
            .def("SetDirection", &Physics::SetDirection)
			.def("SetPhysConstants", &Physics::SetPhysConstants)
			.def("SetBox", &Physics::SetBox)
			.def("SetMap", &Physics::SetMap)

			.enum_("MOVE")[
				value("STOP", Physics::MOVE::STOP)
			]
	];
    return 1;
}