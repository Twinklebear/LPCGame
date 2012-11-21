#include <string>
#include <SDL.h>
#include <luabind/luabind.hpp>
#include "rect.h"
#include "vectors.h"
#include "window.h"
#include "image.h"
#include "text.h"
#include "button.h"

Button::Button() : mFunc(nullptr)
{
    IsUiElement(true);
}
Button::Button(std::string script) : mFunc(nullptr)
{
    IsUiElement(true);
	mScript.OpenScript(script);
}
Button::~Button(){}
void Button::Draw(std::weak_ptr<Camera> camera){
	Rectf pos = mPhysics->Box();
	if (!mUiElement && !camera.expired()){
		pos = Math::FromSceneSpace(camera, pos);
    }
	//Apply appropriate clip for button's state
	Recti clip;
	if (!mClicked)
		clip = mImage.Clip(0);
	else
		clip = mImage.Clip(1);
	Window::Draw(&mImage, pos, &clip);

	//Draw the text
    Recti textBox((pos.X() + pos.W() / 2) - mText.W() / 2, (pos.Y() + pos.H() / 2) - mText.H() / 2,
        mText.W(), mText.H());
	Window::Draw(&mText, textBox);
}
void Button::OnClick(){
	if (mFunc != nullptr)
		mFunc(mParam);
	if (!mScript.Open())
		return;
	///Call the script
	try{
		luabind::call_function<void>(mScript.Get(), "OnClick");
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
int Button::RegisterLua(lua_State *l){
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
    return 1;
}
