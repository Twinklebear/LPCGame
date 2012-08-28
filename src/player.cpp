#include <cmath>
#include <sstream>
#include "SDL.h"
#include "../externals/json/json.h"
#include "base.h"
#include "math.h"
#include "window.h"
#include "input.h"
#include "image.h"
#include "player.h"

Player::Player(){}
Player::~Player(){}
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

	//Update active animation
	if (mPhysics.State() == MotionState::IDLE && mAnimatedImage.Playing() != "idle")
		mAnimatedImage.Play("idle");
	else if (mPhysics.State() == MotionState::RUNNING && mAnimatedImage.Playing() != "run")
		mAnimatedImage.Play("run");

	//Update animation from
	mAnimatedImage.Update();
}
void Player::Move(float deltaT){
	mPhysics.Move(deltaT);
}
void Player::Draw(Camera *cam){
	Rectf pos = mPhysics.Box();
	if (cam != nullptr)
		pos = Math::FromSceneSpace(cam, pos);

	//Window::Draw(&mImage, pos);
	//Draw animation
	Window::Draw(&mAnimatedImage, pos, &(SDL_Rect)mAnimatedImage.Clip(mAnimatedImage.ActiveClip()));
}
Json::Value Player::Save(){
	//Json::Value val = GameObject::Save();
	//Overriding to test my animated image
	Json::Value val;
	val["physics"] = mPhysics.Save();
	val["tag"]	   = mTag;
	val["obj"]     = "player";
	val["image"]   = mAnimatedImage.Save();
	return val;
}
void Player::Load(Json::Value val){
	//GameObject::Load(val);
	//Overriding to test my animated image
	mPhysics.Load(val["physics"]);
	mAnimatedImage.Load(val["image"]);
	mTag = val["tag"].asString();
	//start idle animation
	mAnimatedImage.Play("idle");
}