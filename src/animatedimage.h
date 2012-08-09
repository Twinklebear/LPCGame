#ifndef ANIMATEDIMAGE_H
#define ANIMATEDIMAGE_H

#include <vector>
#include <string>
#include <SDL.h>
#include "base.h"
#include "window.h"
#include "image.h"

///Describes an animation sequence
struct AnimationSequence {
	///The clips in the animated image clip array
	std::vector<int> clipIndices;
	///The framerate to play the animation at
	int frameRate;
	///The current frame being shown
	int currentFrame;
	///The sequence name
	std::string name;
};

///An image that can store and play animation sequences
/**
*  Used for storing and playing animation sequences,
*  inherits from Image
*/
class AnimatedImage : public Image {
public:
	AnimatedImage();
	~AnimatedImage();

	/**
	*  Save an image's properties to a Json::Value and return it
	*  @return Json::Value containing the information about the image
	*/
	virtual Json::Value Save();
	/**
	*  Load an image and its properties from a Json::Value
	*  @param val The Json::Value to load from
	*/
	virtual void Load(Json::Value val);
private:
	std::vector<AnimationSequence> mSequences;
	///Count the frames elapsed
	int mFrameCounter;
};

#endif