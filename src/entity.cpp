#include "math.h"
#include "entity.h"

Entity::Entity() : mMouseOver(false){
}
void Entity::OnMouseDown(){}
void Entity::OnMouseUp(){}
void Entity::OnMouseEnter(){}
void Entity::OnMouseExit(){}
void Entity::CheckMouseOver(const Vector2f &pos){
	//Only trigger OnMouseEnter if the mouse is colliding and wasn't before
	if (Math::CheckCollision(pos, mPhysics.Box()) && !mMouseOver){
		OnMouseEnter();
		mMouseOver = true;
	}
	//Only trigger mouse exit if the mouse was colliding, but isn't anymore
	else if (!Math::CheckCollision(pos, mPhysics.Box()) && mMouseOver){
		OnMouseExit();
		mMouseOver = false;
	}
}
bool Entity::GetMouseOver(){
	return mMouseOver;

}
bool Entity::HasTag(std::string tag){
	return (mTag == tag);
}
Json::Value Entity::Save(){
	Json::Value val;
	val["image"]   = mImage.Save();
	val["physics"] = mPhysics.Save();
	val["tag"]	   = mTag;
	return val;
}
void Entity::Load(Json::Value val){
	mPhysics.Load(val["physics"]);
	mImage.Load(val["image"]);
	mTag = val["tag"].asString();
}
