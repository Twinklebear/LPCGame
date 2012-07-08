#include <cmath>
#include <sstream>
#include "SDL.h"
#include "gameobject.h"
#include "rect.h"
#include "vectors.h"
#include "math.h"
#include "physics.h"
#include "window.h"
#include "image.h"
#include "npc.h"
#include "player.h"


Npc::Npc(){
	//Setup position and physical constants
	Vector2f pos(50, 50);
	mPhysics.SetPosition(pos);
	PhysicalConstants physConst;
	physConst.w			= PLAYER_WIDTH;
	physConst.h			= PLAYER_HEIGHT;
	physConst.hSpeed	= PLAYER_HSPEED;
	physConst.hAccel	= PLAYER_HACCEL;
	mPhysics.SetPhysConstants(physConst);
	//load image
	mImage.LoadImage("images/image.png");
	mImage.SetPos(pos);
}
Npc::~Npc(){
}
void Npc::Move(float deltaT){
	mPhysics.Move(deltaT);
	mImage.SetPos(mPhysics.GetPosition());
}
void Npc::Draw(){
	Window::Draw(&mImage, (SDL_Rect)mImage.Box());
}
Rectf Npc::Box(){
	return mImage.Box();
}
void Npc::SetMove(int move){
	if (move == Math::LEFT || move == Math::RIGHT)
		mPhysics.SetHorizDir(move);
	else if (move == Math::UP || move == Math::DOWN)
		mPhysics.SetVertDir(move);
	else if (move == Physics::MOVE::STOP){
		mPhysics.SetHorizDir(move);
		mPhysics.SetVertDir(move);
	}
}