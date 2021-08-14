#pragma once
#include <SDL.h>

class Timer {

public:

	static Timer* Instance();
	static void Release();

	void Reset();
	float DeltaTime();

	void Update();

private:

	static Timer* sInstance;

	unsigned int mStartTicks;
	unsigned int mElapsedTicks;
	float mDeltaTime;

	Timer();
};