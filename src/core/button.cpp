#include <string>
#include <SDL.h>
#include "rect.h"
#include "vectors.h"
#include "window.h"
#include "image.h"
#include "text.h"
#include "luascript.h"
#include "button.h"

Button::Button() : mFunc(nullptr)
{
    IsUiElement(true);
}
Button::Button(std::string script) : mFunc(nullptr)
{
    IsUiElement(true);
	mScript->OpenScript(script);
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
    //TODO: The distinction between button and entity will be
    //defined in scripts from now on. Button and ObjectButton will become obsolete.
	//if (mFunc != nullptr)
	//	mFunc(mParam);
	//if (!mScript.Open())
	//	return;
	/////Call the script
	//try{
	//	luabind::call_function<void>(mScript.Get(), "OnClick");
	//}
	//catch(...){
	//}
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