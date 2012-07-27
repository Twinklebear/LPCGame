#include <memory>
#include "math.h"
#include "window.h"
#include "rect.h"
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
	Rectf winBox = Window::Box();
	//TODO: winbox here 
	mBox.w = winBox.w;
	mBox.h = winBox.h;
	//Adjust camera position
	float x, y;
	x = (mBox.w + focBox.w / 2) - mBox.w / 2;
	y = (mBox.h + focBox.h / 2) - mBox.h / 2;
	//Clamp the camera values to keep them in range
	mBox.Set(Math::Clamp(x, 0, winBox.w - mBox.w), 
		Math::Clamp(y, 0, winBox.h - mBox.h));
}
bool Camera::InCamera(Rectf box) const{
	return Math::CheckCollision(mBox, box);
}
void Camera::SetBox(Rectf box){
	mBox = box;
}
Rectf Camera::Box() const{
	return mBox;
}
Vector2f Camera::Offset() const{
	return Vector2f(mBox.X(), mBox.Y());
}
