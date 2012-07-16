#include <cmath>
#include <sstream>
#include "SDL.h"
#include "gameobject.h"
#include "rect.h"
#include "vectors.h"
#include "math.h"
#include "window.h"
#include "input.h"
#include "image.h"
#include "player.h"

#include <iostream>

Player::Player(){
	dbg = new Debugger("Player.txt");
}
Player::~Player(){
	delete dbg;
}
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
void Player::OnMouseDown(){
	dbg->Write("Mouse down on player");
}
void Player::OnMouseUp(){
	dbg->Write("Mouse up on player");
}