#include <string>
#include <stdexcept>
#include <memory>
#include "SDL.h"
#include "SDL_ttf.h"
#include "json/json.h"
#include "rect.h"
#include "window.h"
#include "text.h"

Text::Text() : mFont(nullptr, TTF_CloseFont), mTex(nullptr, SDL_DestroyTexture), mMessage(""), mFontSize(0)
{
	mColor.r = 0;
	mColor.g = 0;
	mColor.b = 0;
}
Text::Text(std::string message, std::string font, SDL_Color color, int fontSize) 
	: mFont(nullptr, TTF_CloseFont), mTex(nullptr, SDL_DestroyTexture)
{
	try {
		Setup(message, font, color, fontSize);
	}
	catch (const std::runtime_error &e){
		throw e;
	}
}
Text::~Text(){}
void Text::Setup(std::string message, std::string font, SDL_Color color, int fontSize){
	//Set the class variables to match desired setup
	mMessage  = message;
	mColor    = color;
	mFontSize = fontSize;
	mFontFile = font;

	//Open the font
	mFont.reset(TTF_OpenFont(mFontFile.c_str(), mFontSize), TTF_CloseFont);
	if (mFont == nullptr)
		throw std::runtime_error("Failed to open font: " + font);

	//Render the message and convert to texture
	mTex.reset(Window::SurfaceToTexture(TTF_RenderUTF8_Blended(mFont.get(), mMessage.c_str(), mColor)),
		SDL_DestroyTexture);
	if (mTex == nullptr)
		throw std::runtime_error("Failed to set message texture");
}
void Text::SetMessage(std::string message){
	//Make sure we don't do it if the messages already match
	if (mMessage == message)
		return;
	//Render the new message
	mTex.reset(Window::SurfaceToTexture(TTF_RenderUTF8_Blended(mFont.get(), mMessage.c_str(), mColor)),
		SDL_DestroyTexture);
	if (mTex == nullptr)
		throw std::runtime_error("Failed to set message texture");
}
void Text::SetFont(std::string font){
	mFontFile = font;
	//Load the new font
	mFont.reset(TTF_OpenFont(mFontFile.c_str(), mFontSize), TTF_CloseFont);
	if (mFont == nullptr)
		throw std::runtime_error("Failed to open font: " + font);	
}
void Text::SetFontSize(int fontSize){
	mFontSize = fontSize;
	//Reload font with new fontsize
	mFont.reset(TTF_OpenFont(mFontFile.c_str(), mFontSize), TTF_CloseFont);
	if (mFont == nullptr)
		throw std::runtime_error("Failed to open font: " + mFontFile);	
}
void Text::SetColor(SDL_Color color){
	if (mColor.r == color.r && mColor.g == color.g && mColor.b == color.b)
		return;
	mColor = color;
	//Render the new message
	mTex.reset(Window::SurfaceToTexture(TTF_RenderUTF8_Blended(mFont.get(), mMessage.c_str(), mColor)),
		SDL_DestroyTexture);
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
	val["message"] 	  = mMessage;
	val["font"]	   	  = mFontFile;
	val["fontsize"]   = mFontSize;
	val["color"]["r"] = mColor.r;
	val["color"]["g"] = mColor.g;
	val["color"]["b"] = mColor.b;

	return val;	
}
void Text::Load(Json::Value value){
	SDL_Color col;
	col.r = value["color"]["r"].asInt();
	col.g = value["color"]["g"].asInt();
	col.b = value["color"]["b"].asInt();

	Setup(value["message"].asString(), value["font"].asString(), 
		col, value["fontsize"].asInt());
}