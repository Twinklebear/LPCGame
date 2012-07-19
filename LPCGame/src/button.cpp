#include <string>
#include "SDL.h"
#include "rect.h"
#include "vectors.h"
#include "window.h"
#include "gameobject.h"
#include "image.h"
#include "button.h"

Button::Button() : mFunc(nullptr), mClicked(false)
{
}
Button::Button(int x, int y, std::string text, int w, int h) : mFunc(nullptr), mClicked(false)
{
}
Button::~Button(){}
void Button::Start(int x, int y){
	Rectf box(x, y, 200, 100);
	mPhysics.SetBox(box);
	//setup physical constants
	PhysicalConstants physConst;
	physConst.hSpeed	= 0;
	physConst.hAccel	= 0;
	mPhysics.SetPhysConstants(physConst);
	mClicked = false;

	mImage.LoadImage("images/200x100button.png");
	//Setup image clips
	std::vector<Recti> clips;
	clips.push_back(Recti(0, 0, 200, 100));
	clips.push_back(Recti(0, 100, 200, 100));
	mImage.SetClips(clips);
}
void Button::Update(){}
void Button::Draw(){
	if (!mClicked)
		Window::Draw(&mImage, (SDL_Rect)mPhysics.Box(), &(SDL_Rect)mImage.Clip(0));
	else
		Window::Draw(&mImage, (SDL_Rect)mPhysics.Box(), &(SDL_Rect)mImage.Clip(1));
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
		mFunc();
}
/*
void RegisterCallBack(object *obj, void (object::*func)()){
	mObj = obj;
	mObjFunc = func;
	mFunc = nullptr;
*/
void Button::RegisterCallBack(void (*f)()){
	mFunc = f;
}