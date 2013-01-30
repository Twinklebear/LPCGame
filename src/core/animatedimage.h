#ifndef ANIMATEDIMAGE_H
#define ANIMATEDIMAGE_H

#include <vector>
#include <string>
#include <SDL.h>
#include "base.h"
#include "image.h"
#include "timer.h"

///Describes an animation sequence
struct AnimationSequence {
	/**
	*  Save the sequence to a Json::Value
	*  @return The sequence information as a Json::Value
	*/
	Json::Value Save() const;
	/**
	*  Load the sequence from a Json::Value
	*  @param val The Json::Value to load from
	*/
	void Load(Json::Value val);
	///The clips in the animated image clip array
	std::vector<int> clipIndices;
	///The framerate to play the animation at
	double frameRate;
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
    /**
    *  Setup the AnimatedImage class, if a filename is passed load the image
    *  @param file The filename
    *  @see Window::LoadImage for the loading function
    */
    AnimatedImage(const std::string &file);
    AnimatedImage();
	~AnimatedImage();
	/**
	*  Update the animation, called every frame
    *  We check if time greater than the time for one frame (1 / frameRate)
    *  and if yes we then increment the frame counter by the # frames elapsed
    *  in case the animation frameRate is higher than the game framerate
	*/
	void Update();
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
	*  Save an AniamtedImage's properties to a Json formatted file
    *  @param file The file to save to
	*/
	void Save(const std::string &file) const;

private:
    /**
	*  Load an AnimatedImage's properties from a Json::Value
	*  @param val The Json::Value to load from
	*/
	void Load(Json::Value val);

private:
	std::vector<AnimationSequence> mSequences;
    int mActiveAnimation;
    ///The current frame of the animation
    int mFrame;
    ///The timer for the animation, for regulating framerate
    Timer mTimer;
};

#endif