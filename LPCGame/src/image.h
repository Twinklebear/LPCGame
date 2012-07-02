#ifndef IMAGE_H
#define IMAGE_H

#include <string>
#include <vector>
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
	/**
	*	Move the rect by some vector
	*	@param vect: the vector to move the position along
	*/
	void Move(Vector2f vect);
	///Getters & Setters
	SDL_Surface* Surface();
	Rectf Box();
	Recti Clip(int clipNum);
	void SetPos(float x, float y);
	void SetPos(Vector2f vec);
	void SetClips(const std::vector<Recti> &clips);

private:
	//We do this so to block out copy-construction, which can cause many issues
	Image(const Image &a);
	Image& operator = (const Image &a);

private:
	SDL_Surface *mSurface;
	Recti *mClips;
	Rectf mRect;
	int mNumClips;
};

#endif