#include <string>
#include <stdexcept>
#include <memory>
#include <SDL.h>
#include <SDL_ttf.h>
#include <luabind/luabind.hpp>
#include "../externals/json/json.h"
#include "rect.h"
#include "window.h"
#include "color.h"
#include "text.h"

Text::Text() : mTex(nullptr, SDL_DestroyTexture), mMessage(""), mFontSize(0)
{
}
Text::Text(std::string message, std::string font, Color color, int fontSize) 
	: mTex(nullptr, SDL_DestroyTexture)
{
	try {
		Set(message, font, color, fontSize);
	}
	catch (const std::runtime_error &e){
		throw e;
	}
}
Text::~Text(){}
void Text::Set(std::string message, std::string font, Color color, int fontSize){
	mMessage  = message;
	mColor	  = color;
	mFontFile = font;
	mFontSize = fontSize;
	try {
		mTex.reset(Window::RenderText(mMessage, mFontFile, mColor, mFontSize), SDL_DestroyTexture);
	}
	catch (const std::runtime_error &e){
		throw e;
	}
	if (mTex == nullptr)
		throw std::runtime_error("Failed to setup message");
}
void Text::SetMessage(std::string message){
	//Make sure we don't do it if the messages already match
	if (mMessage == message)
		return;
	//Render the new message
	mMessage = message;
	mTex.reset(Window::RenderText(mMessage, mFontFile, mColor, mFontSize), SDL_DestroyTexture);
	if (mTex == nullptr)
		throw std::runtime_error("Failed to set message texture");
}
void Text::SetFont(std::string font){
	if (mFontFile == font)
		return;
	mFontFile = font;
	//Load the new font
	mTex.reset(Window::RenderText(mMessage, mFontFile, mColor, mFontSize), SDL_DestroyTexture);
	if (mTex == nullptr)
		throw std::runtime_error("Failed to set message texture");
}
void Text::SetFontSize(int fontSize){
	if (mFontSize == fontSize)
		return;
	mFontSize = fontSize;
	//Reload font with new fontsize
	mTex.reset(Window::RenderText(mMessage, mFontFile, mColor, mFontSize), SDL_DestroyTexture);
	if (mTex == nullptr)
		throw std::runtime_error("Failed to open font: " + mFontFile);	
}
void Text::SetColor(Color color){
	if (mColor == color)
		return;
	mColor = color;
	//Render the new message
	mTex.reset(Window::RenderText(mMessage, mFontFile, mColor, mFontSize), SDL_DestroyTexture);
	if (mTex == nullptr)
		throw std::runtime_error("Failed to set message texture");
}
SDL_Texture* Text::Texture(){
	return mTex.get();
}
Recti Text::GetSize(){
	Recti box(0, 0, 0, 0);
	SDL_QueryTexture(mTex.get(), NULL, NULL, &box.w, &box.h);
	return box;
}
void Text::GetSize(int &w, int &h){
	SDL_QueryTexture(mTex.get(), NULL, NULL, &w, &h);
}
Json::Value Text::Save(){
	Json::Value val;
	val["message"] 	= mMessage;
	val["font"]	   	= mFontFile;
	val["fontsize"] = mFontSize;
	val["color"]	= mColor.Save();
	return val;	
}
void Text::Load(Json::Value val){
	mColor.Load(val["color"]);
	Set(val["message"].asString(), val["font"].asString(), 
		mColor, val["fontsize"].asInt());
}
void Text::RegisterLua(lua_State *l){
	using namespace luabind;

	module(l, "LPC")[
		class_<Text>("Text")
			.def(constructor<>())
			//.def(constructor<std::string, std::string, 
	];
}