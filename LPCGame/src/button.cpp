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
void Button::Draw(){
	if (!mClicked)
		Window::Draw(&mImage, (SDL_Rect)mPhysics.Box(), &(SDL_Rect)mImage.Clip(0));
	else
		Window::Draw(&mImage, (SDL_Rect)mPhysics.Box(), &(SDL_Rect)mImage.Clip(1));
	//Draw the text
	Recti textBox = mText.GetSize();
	Rectf buttonBox = mPhysics.Box();
	textBox.pos.x = (buttonBox.X() + buttonBox.W() / 2) - textBox.W() / 2;
	textBox.pos.y = (buttonBox.Y() + buttonBox.H() / 2) - textBox.H() / 2;
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
	//Run the button activity here
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