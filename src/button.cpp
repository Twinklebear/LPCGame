#include <string>
#include <SDL.h>
#include <luabind/luabind.hpp>
#include "rect.h"
#include "vectors.h"
#include "window.h"
#include "image.h"
#include "text.h"
#include "button.h"

Button::Button() : mClicked(false), mFunc(nullptr)
{
}
Button::Button(std::string script) : mClicked(false), mFunc(nullptr)
{
	OpenScript(script);
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
	///Call the script
	Entity::OnMouseDown();
}
void Button::OnMouseUp(){
	if (mClicked)
		OnClick();
	mClicked = false;
	///Call the script
	Entity::OnMouseUp();
}
void Button::OnMouseEnter(){
	//maybe a lighter highlight?
	///Call the script
	Entity::OnMouseEnter();
}
void Button::OnMouseExit(){
	mClicked = false;
	///Call the script
	Entity::OnMouseExit();
}
void Button::OnClick(){
	if (mFunc != nullptr)
		mFunc(mParam);
	///Call the script
	try{
		luabind::call_function<void>(mL, "OnClick");
	}
	catch(...){
	}
}
void Button::RegisterCallBack(void (*f)(std::string), std::string param){
	mFunc = f;
	mParam = param;
}
Json::Value Button::Save(){
	Json::Value val = Entity::Save();
	val["type"]	   = "button";
	val["text"]    = mText.Save();
	val["param"]   = mParam;

	return val;
}
void Button::Load(Json::Value val){
	Entity::Load(val);
	mParam = val["param"].asString();
	mText.Load(val["text"]);
}
void Button::RegisterLua(lua_State *l){
	using namespace luabind;

	module(l, "LPC")[
		class_<Button>("Button")
			.def(constructor<>())
			.def(constructor<std::string>())
			.def("Init", &Entity::Init)
			.def("Update", &Entity::Update)
			.def("Draw", &Entity::Draw)
			.def("Move", &Entity::Move)
			.def("OnMouseDown", &Button::OnMouseDown)
			.def("OnMouseUp", &Button::OnMouseUp)
			.def("OnMouseEnter", &Button::OnMouseEnter)
			.def("OnMouseExit", &Button::OnMouseExit)
			.def("OnClick", &Button::OnClick)
	];
}
