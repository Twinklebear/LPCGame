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

#include <iostream>

Player::Player(){}
Player::~Player(){}
void Player::Update(){
	//Horizontal input handling

	//direction the player is facing
	int direction = -1;

	if (Input::KeyDown("a")){
		mPhysics.SetHorizDir(Math::LEFT);
		direction = Math::LEFT;
	}
	else if (Input::KeyDown("d")){
		mPhysics.SetHorizDir(Math::RIGHT);
		direction = Math::RIGHT;
	}
	else
		mPhysics.SetHorizDir(Physics::MOVE::STOP);
	//Vertical input handling
	if (Input::KeyDown("w")){
		mPhysics.SetVertDir(Math::UP);
		direction = Math::UP;
	}
	else if (Input::KeyDown("s")){
		mPhysics.SetVertDir(Math::DOWN);
		direction = Math::DOWN;
	}
	else
		mPhysics.SetVertDir(Physics::MOVE::STOP);

	//Update active animation

	if (mPhysics.State() == MotionState::IDLE){
		if (mAnimatedImage.Playing() == "run-left")
			mAnimatedImage.Play("idle-left");
		else if (mAnimatedImage.Playing() == "run-right")
			mAnimatedImage.Play("idle-right");
		else if (mAnimatedImage.Playing() == "run-up")
			mAnimatedImage.Play("idle-up");
		else if (mAnimatedImage.Playing() == "run-down")
			mAnimatedImage.Play("idle-down");
	}
	else if (mPhysics.State() == MotionState::RUNNING){
		if (direction == Math::LEFT && mAnimatedImage.Playing() != "run-left")
			mAnimatedImage.Play("run-left");
		else if (direction == Math::RIGHT && mAnimatedImage.Playing() != "run-right")
			mAnimatedImage.Play("run-right");
		else if (direction == Math::UP && mAnimatedImage.Playing() != "run-up")
			mAnimatedImage.Play("run-up");
		else if (direction == Math::DOWN && mAnimatedImage.Playing() != "run-down")
			mAnimatedImage.Play("run-down");
	}
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
	Window::Draw(&mAnimatedImage, pos, &(Recti)mAnimatedImage.Clip(mAnimatedImage.ActiveClip()));
}
Json::Value Player::Save(){
	//Overriding to test my animated image
	Json::Value val;
	val["physics"] = mPhysics.Save();
	val["tag"]	   = mTag;
	val["obj"]     = "player";
	val["image"]   = mAnimatedImage.Save();
	return val;
}
void Player::Load(Json::Value val){
	//Overriding to test my animated image
	mPhysics.Load(val["physics"]);
	mAnimatedImage.Load(val["image"]);
	mTag = val["tag"].asString();
	//start idle animation
	mAnimatedImage.Play("idle-left");
}