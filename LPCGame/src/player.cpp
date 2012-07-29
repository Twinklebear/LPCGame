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
void Player::Draw(Camera *cam){
	if (cam == nullptr)
		Window::Draw(&mImage, (SDL_Rect)mPhysics.Box());
	else {
		Rectf pos(mPhysics.Box().X() + cam->Centering().x, mPhysics.Box().Y() + cam->Centering().y,
			mPhysics.Box().w, mPhysics.Box().h);
		Window::Draw(&mImage, pos);
	}
}
Json::Value Player::Save(){
	Json::Value val;
	val["obj"]     = "player";
	val["physics"] = mPhysics.Save();
	val["image"]   = mImage.Save();

	return val;
}
void Player::Load(Json::Value val){
	mImage.Load(val["image"]);
	mPhysics.Load(val["physics"]);
}