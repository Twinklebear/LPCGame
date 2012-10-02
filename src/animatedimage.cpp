#include <vector>
#include <string>
#include <SDL.h>
#include <luabind/luabind.hpp>
#include "base.h"
#include "window.h"
#include "image.h"
#include "timer.h"
#include "animatedimage.h"

Json::Value AnimationSequence::Save(){
	Json::Value val;
	val["framePerAnimFrame"] = framePerAnimFrame;
	val["name"] = name;
	//Save the indices
	for (int i = 0; i < clipIndices.size(); ++i)
		val["frames"][i] = clipIndices.at(i);
	
	return val;
}
void AnimationSequence::Load(Json::Value val){
	framePerAnimFrame = val["framePerAnimFrame"].asInt();
	name = val["name"].asString();
	//Load the indices
	for (int i = 0; i < val["frames"].size(); ++i){
		clipIndices.push_back(val["frames"][i].asInt());
	}
}
AnimatedImage::AnimatedImage() 
    : mActiveAnimation(0), mFrame(0)
{
}
AnimatedImage::AnimatedImage(const std::string &file) 
    : mActiveAnimation(0), mFrame(0)
{
    //Try to load an image config
    try {
        LoadImage(file);
    }
    catch (const std::runtime_error &e){
        std::cout << e.what() << std::endl;
    }
}
AnimatedImage::~AnimatedImage(){
}
void AnimatedImage::Update(){
    //Using the timer for framerate regulation
    /*
    if (mTimer.Ticks() / 1000.0f >= 1.0f / mSequences.at(mActiveAnimation).frameRate){
        ++mFrame;
        mTimer.Start();
    }
    */
	++mFrame;
	//Update animation frame when we hit the increment value, framePerAnimFrame
	if (mFrame >= mSequences.at(mActiveAnimation).framePerAnimFrame){
		mFrame = 0;
		++mAnimationFrame;
	}
	if (mAnimationFrame >= mSequences.at(mActiveAnimation).clipIndices.size())
		mAnimationFrame = 0;
}
void AnimatedImage::Play(std::string name){
	for (int i = 0; i < mSequences.size(); ++i){
		if (mSequences.at(i).name == name){
			mActiveAnimation = i;
            //Begin the animation
            mFrame = 0;
            //mTimer.Start();
			return;
		}
	}
}
std::string AnimatedImage::Playing(){
    //Should an error be thrown if the sequence vector is empty?
	return mSequences.at(mActiveAnimation).name;
}
int AnimatedImage::ActiveClip(){
	return mSequences.at(mActiveAnimation).clipIndices.at(mAnimationFrame);
}
Json::Value AnimatedImage::Save(){
	//Save base class (file and clips)
	Json::Value val = Image::Save();
	return val;
}
void AnimatedImage::Load(Json::Value val){
	//Load base class (file and clips)
	Image::Load(val);
}
void AnimatedImage::LoadConfig(Json::Value val){
	//Load the clips
	Image::LoadConfig(val);
	//Load the AnimationSequences
	for (int i = 0; i < val["sequences"].size(); ++i){
		AnimationSequence seq;
		seq.Load(val["sequences"][i]);
		mSequences.push_back(seq);
	}
}
void AnimatedImage::RegisterLua(lua_State *l){
	using namespace luabind;

	module(l, "LPC")[
		class_<AnimatedImage>("AnimatedImage")
			.def(constructor<>())
            .def(constructor<std::string>())
			.def("Update", &AnimatedImage::Update)
			.def("Play", &AnimatedImage::Play)
			.def("Playing", &AnimatedImage::Playing)
			.def("ActiveClip", &AnimatedImage::ActiveClip)
			//Inherited members from Image
			.def("LoadImage", &Image::LoadImage)
			.def("SetClips", &Image::SetClips)
			.def("Clip", &Image::Clip)
	];
}
