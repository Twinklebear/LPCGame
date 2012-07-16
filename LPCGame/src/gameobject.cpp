#include "SDL.h"
#include "math.h"
#include "gameobject.h"

GameObject::GameObject(){
	mMouseOver = false;
}
void GameObject::CheckMouseOver(const Vector2f &pos){
	if (Math::CheckCollision(pos, mPhysics.Box())){
		OnMouseEnter();
		mMouseOver = true;
	}
	else {
		if (mMouseOver)
			OnMouseExit();
		mMouseOver = false;
	}
}
bool GameObject::GetMouseOver(){
	return mMouseOver;
}