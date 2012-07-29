#include <memory>
#include "math.h"
#include "window.h"
#include "gameobject.h"
#include "camera.h"

Camera::Camera(){
	mBox.Set(0, 0, Window::Box().W(), Window::Box().H());
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
	//Clamp the camera values to keep them in range
	mBox.Set(Math::Clamp(x, 0, mSceneBox.w - mBox.w), 
		Math::Clamp(y, 0, mSceneBox.h - mBox.h));
}
bool Camera::InCamera(Rectf box) const{
	return Math::CheckCollision(mBox, box);
}
void Camera::SetBox(Rectf box){
	mBox = box;
}
void Camera::SetSceneBox(Rectf box){
	mSceneBox = box;
}
Rectf Camera::Box() const{
	return mBox;
}
Vector2f Camera::Offset() const{
	//TESTING centering the map
	return Vector2f(mBox.X(), mBox.Y());
}
Vector2f Camera::Centering() const{
	return Vector2f((Window::Box().w / 2 - mBox.w / 2), 
		(Window::Box().h / 2 - mBox.h / 2));	
}