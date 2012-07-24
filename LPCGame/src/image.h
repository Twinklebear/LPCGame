#ifndef IMAGE_H
#define IMAGE_H

#include <string>
#include <vector>
#include <memory>
#include "SDL.h"
#include "SDL_image.h"
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
	/**
	*	Load an image from a file to an SDL_Surface*
	*	@param file: the file to load
	*/
	void LoadImage(const std::string file);
	///Getters & Setters
	SDL_Texture* Texture();
	Recti Clip(int clipNum);
	void SetClips(const std::vector<Recti> &clips);

private:
	//We do this so to block out copy-construction, which can cause many issues
	Image(const Image &a);
	Image& operator = (const Image &a);

private:
	//SDL_Texture *mTexture;
	std::shared_ptr<SDL_Texture> mTexture;
	Recti *mClips;
	int mNumClips;
};

#endif