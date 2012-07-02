#ifndef TIMER_H
#define TIMER_H

#include "SDL.h"
/**
*   Timer: A simple timer, needed for calculating FPS, time passed and etc.
*/
class Timer{
public:
    Timer();
    ///Start the time
	void Start();
	///Stop the timer
	void Stop();
	/**
	*	Restart the timer & return the elapsed time
	*	@return the elapsed time
	*/
	int Restart();
	///Pause the timer
    void Pause();
	///Unpause the timer
    void Unpause();
    ///Get the elapsed ticks
    int GetTicks() const;
	bool Started() const;
	bool Paused() const;
private:
	int mStartTicks, mPausedTicks;
	bool mStarted, mPaused;
};

#endif
