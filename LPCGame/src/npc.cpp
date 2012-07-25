#include <cmath>
#include <sstream>
#include "SDL.h"
#include "json/json.h"
#include "gameobject.h"
#include "rect.h"
#include "vectors.h"
#include "math.h"
#include "physics.h"
#include "window.h"
#include "image.h"
#include "npc.h"
#include "player.h"

#include <iostream>

Npc::Npc(){}
Npc::~Npc(){}
void Npc::Start(int x, int y){
	//initialize box
	Rectf box(x, y, PLAYER_WIDTH, PLAYER_HEIGHT);
	mPhysics.SetBox(box);
	PhysicalConstants physConst;
	physConst.hSpeed	= PLAYER_HSPEED;
	physConst.hAccel	= PLAYER_HACCEL;
	mPhysics.SetPhysConstants(physConst);

	//mImage.LoadImage("images/image.png");
}
void Npc::Update(){
	SetMove(Math::DOWN);
}
void Npc::Move(float deltaT){
	mPhysics.Move(deltaT);
}
void Npc::Draw(){
	Window::Draw(&mImage, (SDL_Rect)mPhysics.Box());
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
Json::Value Npc::Save(){
	Json::Value val;
	val["obj"]    = "npc";
	val["type"]   = "0";
	val["x"] 	  = mPhysics.Box().X();
	val["y"] 	  = mPhysics.Box().Y();
	//val["speed"]  = phys constant speed
	//val["accel"]  = phys constant accell
	val["image"]  = "images/image.png";

	return val;
}
void Npc::Load(Json::Value value){
	//Will setup other properties here as well, for now just calling to start
	//at the x, y pos
	mImage.LoadImage(value["image"].asString());
	Start(value["x"].asInt(), value["y"].asInt());
}