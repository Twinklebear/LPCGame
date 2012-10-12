#include <SDL.h>
#include <luabind/luabind.hpp>
#include "timer.h"

Timer::Timer() 
    : mStartTicks(0), mPausedTicks(0), mStarted(false), mPaused(false)
{
}
void Timer::Start(){
	mStarted = true;
	mPaused	 = false;
	mStartTicks = SDL_GetTicks();
}
void Timer::Stop(){
	mStarted = false;
	mPaused	 = false;
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
int Timer::Restart(){
	int elapsedTicks = Ticks();
	Start();
	return elapsedTicks;
}
int Timer::Ticks() const {
    if (mStarted){
	    if (mPaused)
		    return mPausedTicks;
	    else
		    return SDL_GetTicks() - mStartTicks;
    }
    return 0;
}
bool Timer::Started() const {
	return mStarted;
}
bool Timer::Paused() const {
	return mPaused;
}
int Timer::RegisterLua(lua_State *l){
	using namespace luabind;

	module(l, "LPC")[
		class_<Timer>("Timer")
			.def(constructor<>())
			.def("Start", &Timer::Start)
			.def("Stop", &Timer::Stop)
			.def("Restart", &Timer::Restart)
			.def("Pause", &Timer::Pause)
			.def("Unpause", &Timer::Unpause)
			.def("GetTicks", &Timer::Ticks)
			.def("Started", &Timer::Started)
			.def("Paused", &Timer::Paused)
	];
    return 1;
}