#include "SDL.h"
#include "rect.h"
#include "vectors.h"
#include "window.h"
#include "gameobject.h"
#include "image.h"
#include "button.h"

Button::Button(){}
Button::~Button(){}
///Initialize the button
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
///Update the game object
void Button::Update(){}
///Draw the game object
void Button::Draw(){
	if (!mClicked)
		Window::Draw(&mImage, (SDL_Rect)mPhysics.Box(), &(SDL_Rect)mImage.Clip(0));
	else
		Window::Draw(&mImage, (SDL_Rect)mPhysics.Box(), &(SDL_Rect)mImage.Clip(1));
}
///Move the object
void Button::Move(float deltaT){}
///On mouse down events
void Button::OnMouseDown(){
	mClicked = true;
}
///On mouse up event
void Button::OnMouseUp(){
	mClicked = false;
	//Run the button activity here
}
///On mouse enter
void Button::OnMouseEnter(){
	//maybe a lighter highlight?
}
///On mouse exit
void Button::OnMouseExit(){
	mClicked = false;
}