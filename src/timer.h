#ifndef TIMER_H
#define TIMER_H

#include <SDL.h>
#include <luabind/luabind.hpp>

///Measures time, it's a timer
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
    ///Pause the timer
    void Pause();
    ///Unpause the timer
    void Unpause();
    /**
    *  Restart the timer and return the elapsed ticks
    *  @return The elapsed ticks
    */
    int Restart();
    /**
    *  Get the elapsed ticks
    *  @return The elapsed ticks
    */
    int Ticks() const;
    ///Check if Timer is started
    bool Started() const;
    ///Check if Timer is paused
    bool Paused() const;
    /**
    *  Register the Timer class with the lua state
    *  @param l The lua_State to register the module with
    */
    static void RegisterLua(lua_State *l);

private:
	int mStartTicks, mPausedTicks;
	bool mStarted, mPaused;
};

#endif
