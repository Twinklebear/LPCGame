#include <vector>
#include <string>
#include <SDL.h>
#include "base.h"
#include "window.h"
#include "image.h"
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
AnimatedImage::AnimatedImage() : mActiveAnimation(0), mFrame(0) {

}
AnimatedImage::~AnimatedImage(){

}
void AnimatedImage::Update(){
	++mFrame;
	//Update animation frame when we hit the increment value, framePerAnimFrame
	if (mFrame >= mSequences.at(mActiveAnimation).framePerAnimFrame){
		mFrame = 0;
		++mAnimationFrame;
	}
	if (mAnimationFrame >= mSequences.at(mActiveAnimation).clipIndices.size())
		mAnimationFrame = 0;
}
void AnimatedImage::Move(float deltaT){

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
int AnimatedImage::ActiveClip(){
	return mSequences.at(mActiveAnimation).clipIndices.at(mAnimationFrame);
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
