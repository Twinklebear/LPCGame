#include <array>
#include <memory>
#include "SDL.h"
#include "rect.h"
#include "image.h"
#include "window.h"

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
	if (mClips != nullptr)
		delete[] mClips;
}
void Image::LoadImage(const std::string file){
	mTexture.reset(Window::LoadTexture(file), SDL_DestroyTexture);
}
SDL_Texture* Image::Texture(){
	return mTexture.get();
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