#include "Timer.hpp"

Timer::Timer() {
    mStartTicks = 0;
    mPausedTicks = 0;
    mPaused = false;
    mStarted = false;
}

void Timer::start() {
    mStarted = true; //Start the timer
    mPaused = false; //Unpause the timer
    mStartTicks = SDL_GetTicks(); //Get the current clock time
    mPausedTicks = 0;
}

void Timer::stop() {
    mStarted = false; //Stop the timer
    mPaused = false; //Unpause the timer
    mStartTicks = 0;
    mPausedTicks = 0;
}

void Timer::pause() {
    if (mStarted && !mPaused) { //If the timer is running and isn't already paused
        mPaused = true; //Pause the timer
        mPausedTicks = SDL_GetTicks() - mStartTicks; //Calculate the paused ticks
        mStartTicks = 0;
    }
}

void Timer::unpause() {
    if (mStarted && mPaused) { //If the timer is running and paused
        mPaused = false; //Unpause the timer
        mStartTicks = SDL_GetTicks() - mPausedTicks; //Reset the starting ticks
        mPausedTicks = 0; //Reset the paused ticks
    }
}

Uint32 Timer::getTicks() {
    Uint32 time = 0; //The actual timer time
    if (mStarted) { //If the timer is running
        if (mPaused) { //If the timer is paused
            time = mPausedTicks; //Return the number of ticks when the timer was paused
        } else {
            time = SDL_GetTicks() - mStartTicks; //Return the current time minus the start time
        }
    }
    return time;
}

bool Timer::isStarted() {
    return mStarted; //Timer is running and paused or unpaused
}

bool Timer::isPaused() {
    return mPaused && mStarted; //Timer is running and paused
}
