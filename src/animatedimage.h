#ifndef ANIMATEDIMAGE_H
#define ANIMATEDIMAGE_H

#include <vector>
#include <SDL.h>
#include "base.h"
#include "window.h"
#include "image.h"

///An image that can store and play animation sequences
/**
*  Used for storing and playing animation sequences,
*  inherits from Image
*/
class AnimatedImage : public Image {
public:
	AnimatedImage();
	~AnimatedImage();

private:

};

#endif