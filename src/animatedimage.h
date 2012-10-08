#ifndef ANIMATEDIMAGE_H
#define ANIMATEDIMAGE_H

#include <vector>
#include <string>
#include <SDL.h>
#include <luabind/luabind.hpp>
#include "base.h"
#include "image.h"
#include "timer.h"

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
	/**
	*  Load an AnimatedImage settings from a Json::Value
	*  @note This will probably replace Load when the switch is done
	*/
	void LoadConfig(Json::Value val);
	/**
	*  Register the AnimatedImage class with the lua state
	*  @param l The lua_State to register the module with
	*/
	static int RegisterLua(lua_State *l);

private:
	std::vector<AnimationSequence> mSequences;
    int mActiveAnimation;
    ///The current frame of the animation
    int mFrame;
    ///The timer for the animation, for regulating framerate
    Timer mTimer;
};

#endif