#include <array>
#include "SDL.h"
#include "SDL_image.h"
#include "rect.h"
#include "image.h"
#include "window.h"

#include <iostream>

Image::Image(const std::string file){
	mTexture	= nullptr;
	mClips		= nullptr;
	mNumClips	= 0;
	LoadImage(file);
}
Image::Image(){
	mTexture	= nullptr;
	mClips		= nullptr;
	mNumClips	= 0;
}
Image::~Image(){
	if (mTexture != nullptr)
		SDL_DestroyTexture(mTexture);
	if (mClips != nullptr)
		delete[] mClips;
}
void Image::LoadImage(const std::string file){
	//if another image was already loaded, free that one
	if (mTexture != nullptr)
		SDL_DestroyTexture(mTexture);
	mTexture = Window::LoadTexture(file);
}
SDL_Texture* Image::Texture(){
	return mTexture;
}
Recti Image::Clip(int clipNum){
	if (clipNum > mNumClips || clipNum < 0 || mNumClips == 0)
		throw std::runtime_error("Clip num out of bounds");
	return mClips[clipNum];
}
void Image::SetClips(const std::vector<Recti> &clips){
	mNumClips = clips.size();
	mClips = new Recti[clips.size()];
	for (int i = 0; i < clips.size(); ++i)
		mClips[i] = clips.at(i);
}