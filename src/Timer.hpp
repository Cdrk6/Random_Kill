#ifndef TIMER_HPP
#define TIMER_HPP

#include <SDL2/SDL.h>

using namespace std;

class Timer {
  public:
	Timer();
	void start();
	void stop();
	void pause();
	void unpause();
	Uint32 getTicks();
	bool isStarted();
	bool isPaused();

  private:
	Uint32 mStartTicks;
	Uint32 mPausedTicks;
	bool mPaused;
	bool mStarted;
};

#endif /* TIMER_HPP */

