#include <vector>
#include <string>
#include <SDL.h>
#include "base.h"
#include "window.h"
#include "image.h"
#include "animatedimage.h"

Json::Value AnimationSequence::Save(){
	Json::Value val;
	val["framerate"] = frameRate;
	val["name"] = name;
	//Save the indices
	for (int i = 0; i < clipIndices.size(); ++i)
		val["frames"][i] = clipIndices.at(i);
	
	return val;
}
void AnimationSequence::Load(Json::Value val){
	frameRate = val["framerate"].asInt();
	name = val["name"].asString();
	//Load the indices
	for (int i = 0; i < val["frames"].size(); ++i){
		clipIndices.push_back(val["frames"][i].asInt());
	}
}
AnimatedImage::AnimatedImage() : mActiveAnimation(0), mFrame(0) {

}
AnimatedImage::~AnimatedImage(){

}
void AnimatedImage::Update(){
	++mFrame;
	//Reset animation if we go over # of frames in the animation
	if (mFrame >= mSequences.at(mActiveAnimation).clipIndices.size())
		mFrame = 0;
}
void AnimatedImage::Play(std::string name){
	for (int i = 0; i < mSequences.size(); ++i){
		if (mSequences.at(i).name == name){
			mActiveAnimation = i;
			return;
		}
	}
}
std::string AnimatedImage::Playing(){
	return mSequences.at(mActiveAnimation).name;
}
int AnimatedImage::ActiveFrame(){
	return mSequences.at(mActiveAnimation).clipIndices.at(mFrame);
}
Json::Value AnimatedImage::Save(){
	//Save base class (file and clips)
	Json::Value val = Image::Save();
	//Save the sequences
	for (int i = 0; i < mSequences.size(); ++i)
		val["sequences"][i] = mSequences.at(i).Save();

	return val;
}
void AnimatedImage::Load(Json::Value val){
	//Load base class (file and clips)
	Image::Load(val);
	//Load the sequences
	for (int i = 0; i < val["sequences"].size(); ++i){
		AnimationSequence tempSeq;
		tempSeq.Load(val["sequences"][i]);
		mSequences.push_back(tempSeq);
	}
}
