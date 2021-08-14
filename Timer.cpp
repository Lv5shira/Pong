#include "Timer.h"
Timer* Timer::sInstance = NULL;

Timer* Timer::Instance() {

	if (sInstance == NULL)
	{
		sInstance = new Timer();
	}
	return sInstance;
}

void Timer::Release()
{
	delete sInstance;
	sInstance = NULL;
}

Timer::Timer() {
	Reset();
	mElapsedTicks = 0;
	mDeltaTime = 0;
}

void Timer::Reset() {
	mStartTicks = SDL_GetTicks(); //Returns number of milliseconds initialized

}

float Timer::DeltaTime() 
{
	return mDeltaTime;
}

void Timer::Update() {
	mElapsedTicks = SDL_GetTicks() - mStartTicks;
	mDeltaTime = mElapsedTicks * 0.001f; //Convert milliseconds to float, get value in seconds
}