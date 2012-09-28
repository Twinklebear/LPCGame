#include <array>
#include <memory>
#include <fstream>
#include <SDL.h>
#include <luabind/luabind.hpp>
#include "../externals/json/json.h"
#include "rect.h"
#include "window.h"
#include "jsonhandler.h"
#include "image.h"

Image::Image()
	: mTexture(nullptr, SDL_DestroyTexture), mFile(""), mClips(nullptr), mNumClips(0)
{
}
Image::Image(const std::string &file)
	: mTexture(nullptr, SDL_DestroyTexture), mFile(""), mClips(nullptr), mNumClips(0)
{
	mFile = file;
	LoadImage(file);
}
Image::~Image(){
	if (mClips != nullptr)
		delete[] mClips;
}
void Image::LoadImage(const std::string &file){
	mFile = file;
    try {
	    mTexture.reset(Window::LoadTexture(mFile), SDL_DestroyTexture);
        //With the new JsonHandler
        JsonHandler jsonHandler(file);
        LoadConfig(jsonHandler.ReadFile());
    }
    catch (const std::runtime_error &e){
        std::cout << e.what() << std::endl;
    }
}
SDL_Texture* Image::Texture(){
	return mTexture.get();
}
Recti Image::Clip(int clipNum){
	if (clipNum >= mNumClips || clipNum < 0 || mNumClips == 0)
		throw std::runtime_error("Clip num out of bounds");

	return mClips[clipNum];
}
void Image::SetClips(const std::vector<Recti> &clips){
	mNumClips = clips.size();
	mClips = new Recti[mNumClips];
	for (int i = 0; i < mNumClips; ++i)
		mClips[i] = clips.at(i);
}
void Image::GenClips(int cW, int cH){
	//Make sure we've got a texture to query
	if (mTexture == nullptr)
		throw std::runtime_error("Must load texture before genning clips");

	//clear any existing clips
	int iW, iH;
	SDL_QueryTexture(mTexture.get(), NULL, NULL, &iW, &iH);
	//The number of clips is iW / cW * iH / cH
	int numClips = (iW / cW) * (iH / cH);
	mNumClips = numClips;
	mClips = new Recti[mNumClips];
	//Generate the clip rects
	int col = 0;
	//Clips per column
	int cPerCol = (iH / cH);
	for (int i = 0; i < numClips; ++i){
		if (i != 0 && i % cPerCol == 0)
			++col;
		Recti cRect(col * cW, i % cPerCol * cH, cW, cH);
		mClips[i] = cRect;
	}
}
Json::Value Image::Save(){
	Json::Value val;
	val["file"]  = mFile;
	return val;
}
void Image::Load(Json::Value val){
	LoadImage(val["file"].asString());
}
void Image::LoadConfig(Json::Value val){
	if (val["clips"].size() != 0){
		mNumClips = val["clips"].size();
		mClips = new Recti[mNumClips];
		for (int i = 0; i < mNumClips; ++i)
			mClips[i].Load(val["clips"][i]);
	}
}
void Image::RegisterLua(lua_State *l){
	using namespace luabind;

	module(l, "LPC")[
		class_<Image>("Image")
			.def(constructor<>())
			.def(constructor<std::string>())
			.def("LoadImage", &Image::LoadImage)
			.def("SetClips", &Image::SetClips)
			.def("GenClips", &Image::GenClips)
			.def("Clip", &Image::Clip)
	];
}