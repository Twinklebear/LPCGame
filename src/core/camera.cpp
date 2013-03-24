#include <memory>
#include "external/json/json.h"
#include "math.h"
#include "window.h"
#include "entity.h"
#include "camera.h"

Camera::Camera() : mActivePan(-1), mScene("def"){
	mBox.Set(0, 0, Window::Box().w, Window::Box().h);
	mSceneBox.Set(0, 0, 0, 0);
}
Camera::~Camera(){
	mFocus.reset();
}
void Camera::SetFocus(std::shared_ptr<Entity> obj){
	mFocus = obj;
}
void Camera::Update(){
	//TODO: Update camera offsets to apply window centering on resize? The centering offset doesn't
	//seem to work. I tried also applying it to the camera but that didn't seem to help.. Hmm

	//If a pan is set, do that instead of following focus
	if (mActivePan != -1)
		return;

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
	x = (focBox.pos.x + focBox.w / 2) - mBox.w / 2;
	y = (focBox.pos.y + focBox.h / 2) - mBox.h / 2;

	//Clamp the camera values to keep them in range
	mBox.pos = Vector2f(Math::Clamp(x, 0, mSceneBox.w - mBox.w), 
		Math::Clamp(y, 0, mSceneBox.h - mBox.h));
}
bool Camera::InCamera(Rectf box) const{
	return Math::CheckCollision(mBox, box);
}
void Camera::Move(Vector2f v){
	mBox += v;
}
void Camera::Move(float deltaT){
	if (mActivePan != -1){
		//If the distance between the camera and destination is less than the distance moved in a frame,
		//set the camera to the destination
		if (Math::Distance(mBox.pos, mPans.at(mActivePan).destination) <= mPans.at(mActivePan).speed * deltaT){
			mBox.pos = mPans.at(mActivePan).destination;
			mScene = mPans.at(mActivePan).name;
			mActivePan = -1;
			return;
		}
		//If we haven't arrived, continue moving
		mBox.pos += Math::Normalize(mPans.at(mActivePan).destination - mBox.pos) * mPans.at(mActivePan).speed * deltaT;
	}
}
void Camera::Pan(std::string name){
	//Try to find the animation with the name
	for (int i = 0; i < mPans.size(); ++i){
		if (mPans.at(i).name == name){
			mActivePan = i;
			mScene = "busy";
			return;
		}
	}
	//If lookup failed set active to -1, ie none
	mActivePan = -1;
}
std::string Camera::Scene(){
	return mScene;
}
void Camera::SetBox(Rectf box){
	//The camera box can't be bigger than the scene box
	if (mSceneBox.w != 0 && mSceneBox.h != 0){
		mBox.Set(mBox.pos.x, mBox.pos.y, 
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
	mBox.Set(mBox.pos.x, mBox.pos.y,
		Math::Clamp(mBox.w, 0, mSceneBox.w),
		Math::Clamp(mBox.h, 0, mSceneBox.h));
}
Rectf Camera::SceneBox() const{
	return mSceneBox;
}
Rectf Camera::Box() const{
	return mBox;
}
Vector2f Camera::Offset() const{
	return Vector2f(mBox.pos.x - Centering().x, mBox.pos.y - Centering().y);
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
	//save the pan instructions
	for (int i = 0; i < mPans.size(); ++i){
		val["pans"][i]["name"]  = mPans.at(i).name;
		val["pans"][i]["speed"] = mPans.at(i).speed;
		val["pans"][i]["dest"]  = mPans.at(i).destination.Save();
	}

	return val;
}
void Camera::Load(Json::Value val){
	//TOOD: is it possible to store the tag of the focus, and have the 
	//Camera request the focus from the manager?
	
	mSceneBox.Load(val["sceneBox"]);
	//We need to make sure the camera box is a valid size
	Rectf box;
	box.Load(val["mBox"]);
	SetBox(box);

	//Load pan instructions
	for (int i = 0; i < val["pans"].size(); ++i){
		CameraPan pan;
		pan.name = val["pans"][i]["name"].asString();
		pan.speed = val["pans"][i]["speed"].asInt();
		pan.destination.Load(val["pans"][i]["dest"]);
		
		mPans.push_back(pan);
	}
}
bool Camera::operator == (const Camera &c) const {
    Rectf cBox = c.Box();
    return (mBox.pos.x == cBox.pos.x && mBox.pos.y == cBox.pos.y &&
            mBox.w == cBox.w && mBox.h == cBox.h);
}
bool Camera::operator != (const Camera &c) const {
    return !(*this == c);
}
