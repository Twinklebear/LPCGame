#include "SDL.h"
#include "timer.h"

Timer::Timer(){
	mStartTicks		= 0;
	mPausedTicks	= 0;
	mStarted		= false;
	mPaused			= false;
}
void Timer::Start(){
	mStarted	= true;
	mPaused		= false;
	mStartTicks = SDL_GetTicks();
}
void Timer::Stop(){
	mStarted	= false;
	mPaused		= false;
}
int Timer::Restart(){
	int elapsedTicks = GetTicks();
	Start();
	return elapsedTicks;
}
void Timer::Pause(){
	if (mStarted && !mPaused){
		mPaused = true;
		mPausedTicks = SDL_GetTicks() - mStartTicks;
	}
}
void Timer::Unpause(){
	if (mPaused){
		mPaused = false;
		mStartTicks = SDL_GetTicks() - mPausedTicks;
		mPausedTicks = 0;
	}
}
int Timer::GetTicks() const{
	if (mStarted){
		if (mPaused)
			return mPausedTicks;
		else{
			return SDL_GetTicks() - mStartTicks;
		}
	}
	//if timer isn't running return 0
	return 0;
}
bool Timer::Started() const{
	return mStarted;
}
bool Timer::Paused() const{
	return mPaused;
}