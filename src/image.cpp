#include <array>
#include <memory>
#include <fstream>
#include <SDL.h>
#include <luabind/luabind.hpp>
#include "../externals/json/json.h"
#include "rect.h"
#include "window.h"
#include "jsonhandler.h"
#include "debug.h"
#include "image.h"

Image::Image()
	: mTexture(nullptr, SDL_DestroyTexture), mFile(""), mClips(nullptr), mNumClips(0), mActiveClip(-1)
{
}
Image::Image(const std::string &file)
	: mTexture(nullptr, SDL_DestroyTexture), mFile(""), mClips(nullptr), mNumClips(0), mActiveClip(-1)
{
    Load(file);
}
Image::~Image(){
	if (mClips != nullptr)
		delete[] mClips;
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
		Debug::Log("Must load texture before generating clips");

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
void Image::Size(int *w, int *h) const {
    SDL_QueryTexture(mTexture.get(), NULL, NULL, w, h);
}
int Image::W() const {
    int w = -1;
    Size(&w);
    return w;
}
int Image::H() const {
    int h = -1;
    Size(NULL, &h);
    return h;
}
SDL_Texture* Image::Texture(){
	return mTexture.get();
}
Recti Image::Clip(int clipNum) const {
    //If clipnum is out of bounds, return a clip of the whole image
    if (clipNum >= mNumClips || clipNum < 0 || mNumClips == 0){
		Debug::Log("Image::Clip ERROR: " + mFile +  "Clip num out of bounds");
        return Recti(0, 0, W(), H());
    }
	return mClips[clipNum];
}
Recti Image::Clip() const {
    return Clip(mActiveClip);
}
void Image::SetActiveClip(int clip){
    mActiveClip = clip;
}
int Image::ClipCount() const {
	return mNumClips;
}
std::string Image::File() const {
    return mFile;
}
void Image::Save(const std::string &file) const {
    JsonHandler handler(file);
    handler.Write(SaveClips());
}
void Image::Load(Json::Value val){
	if (val["clips"].size() != 0){
		mNumClips = val["clips"].size();
		mClips = new Recti[mNumClips];
		for (int i = 0; i < mNumClips; ++i)
			mClips[i].Load(val["clips"][i]);
	}
}
void Image::Load(const std::string &file){
	mFile = file;
    if (mFile == ""){
        Debug::Log("Image: No filename specified");
        return;
    }
	mTexture.reset(Window::LoadTexture(mFile), SDL_DestroyTexture);
    //With the new JsonHandler
    JsonHandler jsonHandler(file);
    Load(jsonHandler.Read());
}
Json::Value Image::SaveClips() const {
    Json::Value val;
    for (int i = 0; i < mNumClips; ++i){
        val["clips"][i] = mClips[i].Save();
    }
    return val;
}
int Image::RegisterLua(lua_State *l){
	using namespace luabind;

	module(l, "LPC")[
		class_<Image>("Image")
			.def(constructor<>())
			.def(constructor<std::string>())
			.def("Load", (void (Image::*)(const std::string&))&Image::Load)
			.def("SetClips", &Image::SetClips)
			.def("GenClips", &Image::GenClips)
			.def("Clip", (Recti (Image::*)(int) const)&Image::Clip)
            .def("Clip", (Recti (Image::*)() const)&Image::Clip)
            .def("SetActiveClip", &Image::SetActiveClip)
            .def("W", &Image::W)
            .def("H", &Image::H)
	];
    return 1;
}