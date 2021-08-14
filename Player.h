#pragma once
#include <SDL.h>

class Player
{
private:
	int mScore;

public:
	SDL_Rect mPlayer;
	Player();
	float mSpeed;

	int Upbounds;
	int Downbounds;
	//Add Score
	void AddScore();
	//Get Score
	int GetScore();

};