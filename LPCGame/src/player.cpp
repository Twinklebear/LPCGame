#include <cmath>
#include <sstream>
#include "SDL.h"
#include "gameobject.h"
#include "rect.h"
#include "vectors.h"
#include "window.h"
#include "image.h"
#include "player.h"

#include <iostream>

Player::Player(){
	//initialize position
	Vector2f pos(200.0, 400.0);
	mPhysics.SetPosition(pos);
	//setup physical constants
	PhysicalConstants physConst;
	physConst.w			= PLAYER_WIDTH;
	physConst.h			= PLAYER_HEIGHT;
	physConst.hSpeed	= PLAYER_HSPEED;
	physConst.hAccel	= PLAYER_HACCEL;
	mPhysics.SetPhysConstants(physConst);

	mImage.LoadImage("images/image.png");
	mImage.SetPos(pos);
}
Player::~Player(){
}
void Player::HandleEvents(SDL_Event &event){
	if (event.type == SDL_KEYDOWN){
		switch (event.key.keysym.sym){
			case SDLK_a:
				mPhysics.SetHorizDir(Physics::MOVE::LEFT);
				break;
			case SDLK_d:
				mPhysics.SetHorizDir(Physics::MOVE::RIGHT);
				break;
			case SDLK_w:
				mPhysics.SetVertDir(Physics::MOVE::UP);
				break;
			case SDLK_s:
				mPhysics.SetVertDir(Physics::MOVE::DOWN);
				break;
			default: 
				break;
		}
	}
	if (event.type == SDL_KEYUP){
		switch (event.key.keysym.sym){
			case SDLK_a:
				mPhysics.SetHorizDir(Physics::MOVE::STOP);
				break;
			case SDLK_d:
				mPhysics.SetHorizDir(Physics::MOVE::STOP);
				break;
			case SDLK_w:
				mPhysics.SetVertDir(Physics::MOVE::STOP);
				break;
			case SDLK_s:
				mPhysics.SetVertDir(Physics::MOVE::STOP);
				break;
			default:
				break;
		}
	}
}
void Player::Move(float deltaT){
	mPhysics.Move(deltaT);
	mImage.Move(mPhysics.GetFrameMove(deltaT));
}
void Player::Draw(){
	Window::Draw(&mImage, (SDL_Rect)mImage.Box());
}
Rectf Player::Box(){
	return mImage.Box();
}