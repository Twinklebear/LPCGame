#include "SDL.h"
#include "math.h"
#include "gameobject.h"

GameObject::GameObject() : mMouseOver(false){
}
void GameObject::OnMouseDown(){}
void GameObject::OnMouseUp(){}
void GameObject::OnMouseEnter(){}
void GameObject::OnMouseExit(){}
void GameObject::CheckMouseOver(const Vector2f &pos){
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
bool GameObject::GetMouseOver(){
	return mMouseOver;

}
bool GameObject::HasTag(std::string tag){
	for (int i = 0; i < mTags.size(); ++i){
		if (tag == mTags.at(i))
			return true;
	}
	return false;
}
Json::Value GameObject::Save(){
	Json::Value val;
	val["image"]   = mImage.Save();
	val["physics"] = mPhysics.Save();
	for (int i = 0; i < mTags.size(); ++i)
		val["tags"][i] = mTags.at(i);

	return val;
}
void GameObject::Load(Json::Value val){
	mPhysics.Load(val["physics"]);
	mImage.Load(val["image"]);
	for (int i = 0; i < val["tags"].size(); ++i)
		mTags.push_back(val["tags"][i].asString());
}
