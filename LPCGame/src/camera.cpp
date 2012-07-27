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
	//Update width and height to match window size
	Rectf winBox = Window::Box();
	//Try to lock the focus
	auto s = mFocus.lock();
	//If there's no focus don't have the camera try to follow one
	if (!s)
		return;

	Rectf focBox = s->Box();
	std::cout << "Focused: " << focBox.X() << ", "
		<< focBox.Y() << ", " << focBox.w << ", "
		<< focBox.h << std::endl;

	mBox.w = winBox.w;
	mBox.h = winBox.h;
	//Adjust camera position
	float x, y;
	x = (mBox.w + focBox.w / 2) - mBox.w / 2;
	y = (mBox.h + focBox.h / 2) - mBox.h / 2;
	
	//Keep camera on screen
	//TODO: winBox in this case should be the scene box!
	if (mBox.X() + mBox.w > winBox.w)
		x = winBox.w - mBox.w;
	if (mBox.Y() + mBox.h > winBox.h)
		y = winBox.h - mBox.h;
	if (mBox.X() < 0)
		x = 0;
	if (mBox.Y() < 0)
		y = 0;
	std::cout << "Cam x: " << x << " y: " << y << std::endl;
	mBox.Set(x, y);
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
