#include <array>
#include <memory>
#include <fstream>
#include <SDL.h>
#include <luabind/luabind.hpp>
#include "../externals/json/json.h"
#include "rect.h"
#include "image.h"
#include "window.h"

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
    }
    catch (const std::runtime_error &e){
        std::cout << e.what() << std::endl;
        throw e;
    }
    //Try to load a config file
    try {
        LoadConfig(LoadImageConfig(file));
    }
    catch (const std::runtime_error &e){
        std::cout << e.what() << std::endl;
    }
}
SDL_Texture* Image::Texture(){
	return mTexture.get();
}
Recti Image::Clip(int clipNum){
	//if (clipNum >= mClips.size() || clipNum < 0 || mClips.empty() == 0)
	if (clipNum >= mNumClips || clipNum < 0 || mNumClips == 0)
		throw std::runtime_error("Clip num out of bounds");
	//return mClips.at(clipNum);
	return mClips[clipNum];
}
void Image::SetClips(const std::vector<Recti> &clips){
	//mClips.clear();
	//mClips = clips;
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
	//mClips.clear();
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
		//mClips.push_back(cRect);
		mClips[i] = cRect;
	}
}
Json::Value Image::Save(){
	Json::Value val;
	val["file"]  = mFile;
	/*
	for (int i = 0; i < mClips.size(); ++i)
		val["clips"][i] = mClips.at(i).Save();
	*/
	for (int i = 0; i < mNumClips; ++i)
		val["clips"][i] = mClips[i].Save();
	return val;
}
void Image::Load(Json::Value val){
	LoadImage(val["file"].asString());
	//Read in clips if they exist
	/*
	for (int i = 0; i < val["clips"].size(); ++i){
		Recti temp;
		temp.Load(val["clips"][i]);
		mClips.push_back(temp);
	}
	*/
	if (val["clips"].size() != 0){
		mNumClips = val["clips"].size();
		mClips = new Recti[mNumClips];
		for (int i = 0; i < mNumClips; ++i)
			mClips[i].Load(val["clips"][i]);
	}
}
void Image::LoadConfig(Json::Value val){
	/*
	for (int i = 0; i < val["clips"].size(); ++i){
		Recti temp;
		temp.Load(val["clips"][i]);
		mClips.push_back(temp);
	}
	*/
	if (val["clips"].size() != 0){
		mNumClips = val["clips"].size();
		mClips = new Recti[mNumClips];
		for (int i = 0; i < mNumClips; ++i)
			mClips[i].Load(val["clips"][i]);
	}
}
Json::Value Image::LoadImageConfig(const std::string &file){
    size_t extensionPos = file.find_last_of('.');
	std::string configFile = file.substr(0, extensionPos) + ".json";

	//If the file exists, read it in
	std::ifstream fileIn((configFile).c_str(), std::ifstream::binary);
	if (fileIn){
		Json::Reader reader;
		Json::Value root;
		if (reader.parse(fileIn, root, false)){
            fileIn.close();
			return root;
		}
		//some debug output, this case should throw
        else {
            fileIn.close();
            throw std::runtime_error("Failed to parse file: " + configFile); 
        }
	}
    else
        throw std::runtime_error("Failed to find file: " + configFile);
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