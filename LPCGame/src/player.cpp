#include <cmath>
#include <sstream>
#include "SDL.h"
#include "json/json.h"
#include "gameobject.h"
#include "rect.h"
#include "vectors.h"
#include "math.h"
#include "window.h"
#include "input.h"
#include "image.h"
#include "player.h"

Player::Player(){}
Player::~Player(){}
void Player::Start(int x, int y){
	Rectf box(x, y, PLAYER_WIDTH, PLAYER_HEIGHT);
	mPhysics.SetBox(box);
	//setup physical constants
	PhysicalConstants physConst;
	physConst.hSpeed	= PLAYER_HSPEED;
	physConst.hAccel	= PLAYER_HACCEL;
	mPhysics.SetPhysConstants(physConst);

	mImage.LoadImage("images/image.png");
}
void Player::Update(){
	//Horizontal input handling
	if (Input::KeyDown('a'))
		mPhysics.SetHorizDir(Math::LEFT);
	else if (Input::KeyDown('d'))
		mPhysics.SetHorizDir(Math::RIGHT);
	else
		mPhysics.SetHorizDir(Physics::MOVE::STOP);
	//Vertical input handling
	if (Input::KeyDown('w'))
		mPhysics.SetVertDir(Math::UP);
	else if (Input::KeyDown('s'))
		mPhysics.SetVertDir(Math::DOWN);
	else
		mPhysics.SetVertDir(Physics::MOVE::STOP);
}
void Player::Move(float deltaT){
	mPhysics.Move(deltaT);
}
void Player::Draw(){
	Window::Draw(&mImage, (SDL_Rect)mPhysics.Box());
}
Json::Value Player::Save(){
	Json::Value val;
	val["obj"]    = "player";
	val["x"] 	  = mPhysics.Box().X();
	val["y"] 	  = mPhysics.Box().Y();
	//val["speed"]  = phys constant speed
	//val["accel"]  = phys constant accell
	val["image"]  = "images/image.png";

	return val;
}
void Player::Load(Json::Value value){

}