#include <memory>
#include "math.h"
#include "window.h"
#include "gameobject.h"
#include "camera.h"

#include "debugger.h"

Camera::Camera(){
	mBox.Set(0, 0, Window::Box().W(), Window::Box().H());
	mSceneBox.Set(0, 0, 0, 0);
}
Camera::~Camera(){
	mFocus.reset();
}
void Camera::SetFocus(std::shared_ptr<GameObject> obj){
	mFocus = obj;
}
void Camera::Update(){
	//Try to lock the focus weak pointer, ie. check to see if
	//the camera should be following something
	auto s = mFocus.lock();
	//If there's no focus don't have the camera try to follow one
	if (!s)
		return;

	Rectf focBox = s->Box();
	//Update width and height to match window size
	//TODO: Window size in this context SHOULD be the scene size
	//mBox.w = mSceneBox.w;
	//mBox.h = mSceneBox.h;
	//Adjust camera position
	float x, y;
	x = (focBox.X() + focBox.w / 2) - mBox.w / 2;
	y = (focBox.Y() + focBox.h / 2) - mBox.h / 2;

	Debugger::Write("preclamp x:", x);
	Debugger::Write("preclamp y:", y);

	//Clamp the camera values to keep them in range
	mBox.Set(Math::Clamp(x, 0, mSceneBox.w - mBox.w), 
		Math::Clamp(y, 0, mSceneBox.h - mBox.h));

	Debugger::Write("camBox x:", mBox.X());
	Debugger::Write("camBox.y:", mBox.Y());

	Debugger::Write("scene w:", mSceneBox.w);
	Debugger::Write("scene h:", mSceneBox.h);
}
bool Camera::InCamera(Rectf box) const{
	return Math::CheckCollision(mBox, box);
}
void Camera::SetBox(Rectf box){
	//The camera box can't be bigger than the scene box
	if (mSceneBox.w != 0 && mSceneBox.h != 0){
		if (box.w > mSceneBox.w && box.h > mSceneBox.h)
			mBox = mSceneBox;
		else if (box.w > mSceneBox.w && box.h < mSceneBox.h)
			mBox.Set(0, 0, mSceneBox.w, box.h);
		else if (box.w < mSceneBox.w && box.h > mSceneBox.h)
			mBox.Set(0, 0, box.w, mSceneBox.h);
		else
			mBox = box;
	}
	//If no scene box is set yet, just allow the change, as we check again 
	//when setting a scene box
	else
		mBox = box;
}
void Camera::SetSceneBox(Rectf box){
	mSceneBox = box;
	//Make sure the camera is smaller than the scene box
	if (mBox.w > mSceneBox.w && mBox.h > mSceneBox.h)
		mBox = mSceneBox;
	else if (mBox.w > mSceneBox.w && mBox.h < mSceneBox.h)
		mBox.Set(0, 0, mSceneBox.w, mBox.h);
	else if (mBox.w < mSceneBox.w && mBox.h > mSceneBox.h)
		mBox.Set(0, 0, mBox.w, mSceneBox.h);
}
Rectf Camera::Box() const{
	return mBox;
}
Vector2f Camera::Offset() const{
	return Vector2f(mBox.X(), mBox.Y());
}
Vector2f Camera::Centering() const{
	return Vector2f((Window::Box().w / 2 - mSceneBox.w / 2), 
		(Window::Box().h / 2 - mSceneBox.h / 2));	
}