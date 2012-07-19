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
Button::Button(int x, int y, std::string text, int w, int h) : mClicked(false), mFunc(nullptr)
{
	SDL_Color col;
	col.r = 0;
	col.g = 0;
	col.b = 0;
	mText.Setup(text, "fonts/LiberationSans-Regular.ttf", col, 25);
	Start(x, y);
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