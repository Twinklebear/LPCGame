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
	/**
	*  Save the sequence to a Json::Value
	*  @return The sequence information as a Json::Value
	*/
	Json::Value Save();
	/**
	*  Load the sequence from a Json::Value
	*  @param val The Json::Value to load from
	*/
	void Load(Json::Value val);

	///The clips in the animated image clip array
	std::vector<int> clipIndices;
	///The framerate to play the animation at
	//int frameRate;
	int framePerAnimFrame;
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
	*  Update the animation, called every frame
	*/
	void Update();
	/**
	*  Move the animation frame
	*  @param deltaT The time period to play animation over
	*/
	void Move(float deltaT);
	/**
	*  Play the desired animation
	*  @param name The animation name to play
	*/
	void Play(std::string name);
	/**
	*  Get the name of the active animation
	*  @return The name of the animation currently playing
	*/
	std::string Playing();
	/**
	*  Get the clip to apply to the image to show the right frame
	*  @return The current clip to show the right image
	*/
	int ActiveClip();
	/**
	*  Save an image's properties to a Json::Value and return it
	*  @return Json::Value containing the information about the image
	*/
	Json::Value Save();
	/**
	*  Load an image and its properties from a Json::Value
	*  @param val The Json::Value to load from
	*/
	void Load(Json::Value val);

private:
	std::vector<AnimationSequence> mSequences;
	int mActiveAnimation;
	///Count the frames elapsed
	int mFrame;
	///Count the frame the animation is on
	int mAnimationFrame;
};

#endif