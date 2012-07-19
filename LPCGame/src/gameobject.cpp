#include "SDL.h"
#include "math.h"
#include "gameobject.h"

GameObject::GameObject(){
	mMouseOver = false;
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