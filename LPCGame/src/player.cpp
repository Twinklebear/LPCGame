#include <cmath>
#include <sstream>
#include "SDL.h"
#include "gameobject.h"
#include "rect.h"
#include "vectors.h"
#include "math.h"
#include "window.h"
#include "image.h"
#include "player.h"

#include <iostream>

Player::Player(){
	//initialize box
	Rectf box(10, 10, PLAYER_WIDTH, PLAYER_HEIGHT);
	mPhysics.SetBox(box);
	//setup physical constants
	PhysicalConstants physConst;
	physConst.hSpeed	= PLAYER_HSPEED;
	physConst.hAccel	= PLAYER_HACCEL;
	mPhysics.SetPhysConstants(physConst);

	mImage.LoadImage("images/image.png");
}
Player::~Player(){
}
void Player::HandleEvents(SDL_Event &event){
	if (event.type == SDL_KEYDOWN){
		switch (event.key.keysym.sym){
			case SDLK_a:
				mPhysics.SetHorizDir(Math::LEFT);
				break;
			case SDLK_d:
				mPhysics.SetHorizDir(Math::RIGHT);
				break;
			case SDLK_w:
				mPhysics.SetVertDir(Math::UP);
				break;
			case SDLK_s:
				mPhysics.SetVertDir(Math::DOWN);
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
}
void Player::Draw(){
	Window::Draw(&mImage, (SDL_Rect)mPhysics.Box());
}