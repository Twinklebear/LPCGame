#include <memory>
#include "../externals/json/json.h"
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
	std::cout << "Shitty width: " << mBox.w << " h: " << mBox.h << std::endl;
	//TODO: Update camera offsets to apply window centering on resize? The centering offset doesn't
	//seem to work. I tried also applying it to the camera but that didn't seem to help.. Hmm

	//Try to lock the focus weak pointer, ie. check to see if
	//the camera should be following something
	auto s = mFocus.lock();
	//If there's no focus don't have the camera try to follow one
	if (!s){
		return;
	}

	Rectf focBox = s->Box();
	//Adjust camera position
	float x, y;
	x = (focBox.X() + focBox.w / 2) - mBox.w / 2;
	y = (focBox.Y() + focBox.h / 2) - mBox.h / 2;

	//Clamp the camera values to keep them in range
	mBox.Set(Math::Clamp(x, 0, mSceneBox.w - mBox.w), 
		Math::Clamp(y, 0, mSceneBox.h - mBox.h));
}
bool Camera::InCamera(Rectf box) const{
	//return Math::CheckCollision(Math::ToSceneSpace(this, mBox), box);
	return Math::CheckCollision(mBox, box);
}
void Camera::SetBox(Rectf box){
	//The camera box can't be bigger than the scene box
	if (mSceneBox.w != 0 && mSceneBox.h != 0){
		mBox.Set(mBox.X(), mBox.Y(), 
			Math::Clamp(box.w, 0, mSceneBox.w),
			Math::Clamp(box.h, 0, mSceneBox.h));
	}
	//If no scene box is set yet, just allow the change, as we check again 
	//when setting a scene box
	else
		mBox = box;
}
void Camera::SetSceneBox(Rectf box){
	mSceneBox = box;
	//Make sure the camera is smaller than the scene box
	mBox.Set(mBox.X(), mBox.Y(),
		Math::Clamp(mBox.w, 0, mSceneBox.w),
		Math::Clamp(mBox.h, 0, mSceneBox.h));
}
Rectf Camera::Box() const{
	return mBox;
}
Vector2f Camera::Offset() const{
	return Vector2f(mBox.X() - Centering().x, mBox.Y() - Centering().y);
}
Vector2f Camera::Centering() const{
	Recti winBox = Window::Box();
	return Vector2f((winBox.w / 2 - mSceneBox.w / 2), 
		(winBox.h / 2 - mSceneBox.h / 2));	
}
Json::Value Camera::Save(){
	Json::Value val;
	val["mBox"]		= mBox.Save();
	val["sceneBox"] = mSceneBox.Save();

	return val;
}
void Camera::Load(Json::Value val){
	Json::StyledWriter writer;

	mSceneBox.Load(val["sceneBox"]);
	std::cout << writer.write(val["sceneBox"]) << std::endl;

	//We need to make sure the camera box is a valid size
	Rectf box;
	box.Load(val["mBox"]);

	std::cout << writer.write(val["mBox"]) << std::endl;

	SetBox(box);
}