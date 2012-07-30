#include <string>
#include "SDL.h"
#include "rect.h"
#include "vectors.h"
#include "window.h"
#include "gameobject.h"
#include "image.h"
#include "text.h"
#include "button.h"

Button::Button() : mClicked(false), mFunc(nullptr)
{
}
Button::~Button(){}
void Button::Update(){}
void Button::Draw(Camera *cam){
	Rectf pos = mPhysics.Box();
	if (cam != nullptr)
		pos = Math::FromSceneSpace(cam, pos);
	//Apply appropriate clip for button's state
	if (!mClicked)
		Window::Draw(&mImage, pos, &(SDL_Rect)mImage.Clip(0));
	else
		Window::Draw(&mImage, pos, &(SDL_Rect)mImage.Clip(1));
	//Draw the text
	Recti textBox = mText.GetSize();
	textBox.pos.x = (pos.X() + pos.W() / 2) - textBox.W() / 2;
	textBox.pos.y = (pos.Y() + pos.H() / 2) - textBox.H() / 2;
	Window::Draw(&mText, textBox);
}
void Button::Move(float deltaT){}
void Button::OnMouseDown(){
	mClicked = true;
}
void Button::OnMouseUp(){
	if (mClicked)
		OnClick();
	mClicked = false;
}
void Button::OnMouseEnter(){
	//maybe a lighter highlight?
}
void Button::OnMouseExit(){
	mClicked = false;
}
void Button::OnClick(){
	if (mFunc != nullptr)
		mFunc(mParam);
}
void Button::RegisterCallBack(void (*f)(std::string), std::string param){
	mFunc = f;
	mParam = param;
}
Json::Value Button::Save(){
	Json::Value val;
	val["type"]	   = "button";
	val["text"]    = mText.Save();
	val["image"]   = mImage.Save();
	val["physics"] = mPhysics.Save();
	val["param"]   = mParam;
	
	return val;
}
void Button::Load(Json::Value val){
	mParam = val["param"].asString();
	mText.Load(val["text"]);
	mPhysics.Load(val["physics"]);
	mImage.Load(val["image"]);
}