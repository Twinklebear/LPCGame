#include <vector>
#include <string>
#include <SDL.h>
#include "base.h"
#include "window.h"
#include "image.h"
#include "timer.h"
#include "jsonhandler.h"
#include "animatedimage.h"

Json::Value AnimationSequence::Save() const {
	Json::Value val;
    val["frameRate"] = frameRate;
	val["name"] = name;
	//Save the indices
	for (int i = 0; i < clipIndices.size(); ++i)
		val["frames"][i] = clipIndices.at(i);
	
	return val;
}
void AnimationSequence::Load(Json::Value val){
    frameRate = val["frameRate"].asDouble();
	name = val["name"].asString();
	//Load the indices
	for (int i = 0; i < val["frames"].size(); ++i)
		clipIndices.push_back(val["frames"][i].asInt());
}
AnimatedImage::AnimatedImage() 
    : mActiveAnimation(0), mFrame(0)
{
}
AnimatedImage::AnimatedImage(const std::string &file) 
    : mActiveAnimation(0), mFrame(0)
{
    Image::Load(file);
}
AnimatedImage::~AnimatedImage(){
}
void AnimatedImage::Update(){
    //Using the timer for framerate regulation
    if (mSequences.at(mActiveAnimation).frameRate != 0
        && mTimer.Ticks() / 1000.0f >= 1.0f / mSequences.at(mActiveAnimation).frameRate)
    {
        //Increase by frames elapsed
        mFrame += mTimer.Ticks() / (int)((1.0f / mSequences.at(mActiveAnimation).frameRate) * 1000);
        mTimer.Start();
        //Rollover the animation if it goes over
        if (mFrame >= mSequences.at(mActiveAnimation).clipIndices.size())
            mFrame = 0;
        //Update the active clip index
        mActiveClip = mSequences.at(mActiveAnimation).clipIndices.at(mFrame);
    }
}
void AnimatedImage::Play(std::string name){
	for (int i = 0; i < mSequences.size(); ++i){
		if (mSequences.at(i).name == name){
			mActiveAnimation = i;
            //Begin the animation
            mFrame = 0;
            //Set active clip
            mActiveClip = mSequences.at(mActiveAnimation).clipIndices.at(mFrame);
            mTimer.Start();
			return;
		}
	}
}
std::string AnimatedImage::Playing(){
    //Should an error be thrown if the sequence vector is empty?
	return mSequences.at(mActiveAnimation).name;
}
void AnimatedImage::Save(const std::string &file) const {
	//Save base class (file and clips)
	Json::Value val = SaveClips();
    for (int i = 0; i < mSequences.size(); ++i){
        val["sequences"][i] = mSequences.at(i).Save();
    }
    JsonHandler handler(file);
    handler.Write(val);
}
void AnimatedImage::Load(Json::Value val){
	//Load the clips
	Image::Load(val);
	//Load the AnimationSequences
	for (int i = 0; i < val["sequences"].size(); ++i){
		AnimationSequence seq;
		seq.Load(val["sequences"][i]);
		mSequences.push_back(seq);
	}
}
