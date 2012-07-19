#include <string>
#include <stdexcept>
#include "SDL.h"
#include "SDL_ttf.h"
#include "rect.h"
#include "window.h"
#include "text.h"

#include <iostream>

Text::Text() : mFont(nullptr), mTex(nullptr), mMessage(""), mFontSize(0)
{
	mColor.r = 0;
	mColor.g = 0;
	mColor.b = 0;
}
Text::Text(std::string message, std::string font, SDL_Color color, int fontSize) 
	: mFont(nullptr), mTex(nullptr)
{
	try {
		Setup(message, font, color, fontSize);
	}
	catch (const std::runtime_error &e){
		throw e;
	}
}
Text::~Text(){
	SDL_DestroyTexture(mTex);
	TTF_CloseFont(mFont);
}
void Text::Setup(std::string message, std::string font, SDL_Color color, int fontSize){
	mMessage  = message;
	mColor    = color;
	mFontSize = fontSize;
	mFontFile = font;
	//Open the font
	mFont = TTF_OpenFont(mFontFile.c_str(), fontSize);
	if (mFont == nullptr)
		throw std::runtime_error("Failed to open font: " + font);
	//Render the message and convert to texture
	mTex = Window::SurfaceToTexture(TTF_RenderUTF8_Blended(mFont, mMessage.c_str(), mColor));
	if (mTex == nullptr)
		throw std::runtime_error("Failed to set message texture");
}
void Text::SetMessage(std::string message){
	//Make sure we don't do it if the messages already match
	if (mMessage == message)
		return;
	//Destroy existing message
	if (mTex != nullptr){
		SDL_DestroyTexture(mTex);
		mTex = nullptr;
	}
	mTex = Window::SurfaceToTexture(TTF_RenderUTF8_Blended(mFont, mMessage.c_str(), mColor));
	if (mTex == nullptr)
		throw std::runtime_error("Failed to set message texture");
}
void Text::SetFont(std::string font){
	mFontFile = font;
	//Close font if one is open
	if (mFont != nullptr){
		TTF_CloseFont(mFont);
		mFont = nullptr;
	}
	mFont = TTF_OpenFont(mFontFile.c_str(), mFontSize);
	if (mFont == nullptr)
		throw std::runtime_error("Failed to open font: " + font);	
}
void Text::SetFontSize(int fontSize){
	mFontSize = fontSize;
	//Close font if already open
	if (mFont != nullptr){
		TTF_CloseFont(mFont);
		mFont = nullptr;
	}
	mFont = TTF_OpenFont(mFontFile.c_str(), fontSize);
	if (mFont == nullptr)
		throw std::runtime_error("Failed to open font: " + mFontFile);	
}
void Text::SetColor(SDL_Color color){
	if (mColor.r == color.r && mColor.g == color.g && mColor.b == color.b)
		return;
	mColor = color;
	//Destroy existing message
	if (mTex != nullptr){
		SDL_DestroyTexture(mTex);
		mTex = nullptr;
	}
	mTex = Window::SurfaceToTexture(TTF_RenderUTF8_Blended(mFont, mMessage.c_str(), mColor));
	if (mTex == nullptr)
		throw std::runtime_error("Failed to set message texture");
}
SDL_Texture* Text::GetTexture(){
	return mTex;
}
Recti Text::GetSize(){
	Recti box(0, 0, 0, 0);
	SDL_QueryTexture(mTex, NULL, NULL, &box.w, &box.h);
	return box;
}