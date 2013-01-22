#include <string>
#include <stdexcept>
#include <memory>
#include <SDL.h>
#include <SDL_ttf.h>
#include "../externals/json/json.h"
#include "rect.h"
#include "window.h"
#include "color.h"
#include "debug.h"
#include "text.h"

Text::Text() : mTex(nullptr, SDL_DestroyTexture), mMessage(""), mFontSize(0)
{
}
Text::Text(std::string message, std::string font, Color color, int fontSize) 
	: mTex(nullptr, SDL_DestroyTexture)
{
    Set(message, font, color, fontSize);
}
Text::~Text(){}
void Text::Set(std::string message, std::string font, Color color, int fontSize){
	mMessage  = message;
	mColor	  = color;
	mFontFile = font;
	mFontSize = fontSize;
	mTex.reset(Window::RenderText(mMessage, mFontFile, mColor, mFontSize), SDL_DestroyTexture);
	if (mTex == nullptr)
		Debug::Log("Failed to setup text");
}
void Text::SetMessage(std::string message){
	//Make sure we don't do it if the messages already match
	if (mMessage == message)
		return;
	//Render the new message
	mMessage = message;
	mTex.reset(Window::RenderText(mMessage, mFontFile, mColor, mFontSize), SDL_DestroyTexture);
	if (mTex == nullptr)
		Debug::Log("Failed to set message texture");
}
void Text::SetFont(std::string font){
	if (mFontFile == font)
		return;
	mFontFile = font;
	//Load the new font
	mTex.reset(Window::RenderText(mMessage, mFontFile, mColor, mFontSize), SDL_DestroyTexture);
	if (mTex == nullptr)
		Debug::Log("Failed to set message texture");
}
void Text::SetFontSize(int fontSize){
	if (mFontSize == fontSize)
		return;
	mFontSize = fontSize;
	//Reload font with new fontsize
	mTex.reset(Window::RenderText(mMessage, mFontFile, mColor, mFontSize), SDL_DestroyTexture);
	if (mTex == nullptr)
		Debug::Log("Failed to open font: " + mFontFile);	
}
void Text::SetColor(Color color){
	if (mColor == color)
		return;
	mColor = color;
	//Render the new message
	mTex.reset(Window::RenderText(mMessage, mFontFile, mColor, mFontSize), SDL_DestroyTexture);
	if (mTex == nullptr)
		Debug::Log("Failed to set message texture");
}
std::string Text::GetMessage(){
    return mMessage;
}
std::string Text::GetFont(){
    return mFontFile;
}
int Text::GetFontSize(){
    return mFontSize;
}
Color Text::GetColor(){
    return mColor;
}
SDL_Texture* Text::Texture(){
	return mTex.get();
}
Recti Text::Size() const {
	Recti box(0, 0, 0, 0);
	SDL_QueryTexture(mTex.get(), NULL, NULL, &box.w, &box.h);
	return box;
}
void Text::Size(int *w, int *h) const {
	SDL_QueryTexture(mTex.get(), NULL, NULL, w, h);
}
int Text::W() const {
    int w = -1;
    Size(&w);
    return w;
}
int Text::H() const {
    int h = -1;
    Size(NULL, &h);
    return h;
}
Json::Value Text::Save() const {
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
