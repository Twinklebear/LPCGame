#ifndef TIMER_H
#define TIMER_H

#include "SDL.h"

/**
*  A simple timer
*/
class Timer{
public:
    Timer();
    ///Start the timer
	void Start();
	///Stop the timer
	void Stop();
	///Restart the timer and return the elapsed ticks
	int Restart();
	///Pause the timer
    void Pause();
	///Unpause the timer
    void Unpause();
    ///Get the elapsed ticks
    int GetTicks() const;
	///Check if timer is started
	bool Started() const;
	///Check if timer is paused
	bool Paused() const;
private:
	int mStartTicks, mPausedTicks;
	bool mStarted, mPaused;
};

#endif
