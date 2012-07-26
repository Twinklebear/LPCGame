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
void Npc::Update(){

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
	val["obj"]     = "npc";
	val["type"]    = "0";
	val["physics"] = mPhysics.Save();
	val["image"]   = mImage.Save();

	return val;
}
void Npc::Load(Json::Value val){
	mImage.Load(val["image"]);
	mPhysics.Load(val["physics"]);
}