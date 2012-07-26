#ifndef IMAGE_H
#define IMAGE_H

#include <string>
#include <vector>
#include <memory>
#include "SDL.h"
#include "SDL_image.h"
#include "json/json.h"
#include "rect.h"
#include "vectors.h"

/**
*	An image handler, cna be used with FloatRect or IntRect for positioning
*/
class Image{
public:
	/**
	*	Setup the image class, if a filename is passed load the image
	*	@param file: the filename
	*	@see LoadImage for the loading function
	*/
	Image(const std::string file);
	Image();
	~Image();
	/*
	*  Save an image's properties to a Json::Value and return it
	*  Todo: Should i also save clip information here?
	*  @returns: Json::Value containing the information about the image
	*/
	Json::Value Save();
	/*
	*  Load an image and its properties from a Json::Value
	*  @param val: The Json::Value to load from
	*/
	void Load(Json::Value val);
	/*
	*	Load an image from a file to an SDL_Surface*
	*	@param file: the file to load
	*/
	void LoadImage(const std::string file);
	///Getters & Setters
	SDL_Texture* Texture();
	Recti Clip(int clipNum);
	//TODO: Rework the way clips are handled
	void SetClips(const std::vector<Recti> &clips);
	/*
	*  Generate clips based on the desired width and height of each clip
	*  and the size of the image
	*  @param cW: The desired width of each clip
	*  @param cH: The desired height of each clip
	*/
	void GenClips(int cW, int cH);

private:
	//We do this so to block out copy-construction, which can cause many issues
	Image(const Image &a);
	Image& operator = (const Image &a);

private:
	std::shared_ptr<SDL_Texture> mTexture;
	std::string mFile;
	Recti *mClips;
	int mNumClips;
};

#endif