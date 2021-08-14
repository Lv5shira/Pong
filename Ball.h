#pragma once
#include <SDL.h>
#include "Player.h"
#include "Timer.h"

class Ball
{
public:

	Timer* mTimer;
	SDL_Rect mBall;
	Ball();
	~Ball();
	float mSpeedX;
	float mSpeedY;

	int Upbounds;
	int Downbounds;
	int leftBounds;
	int rightBounds;

	void Update(Player& player1, Player& player2);

private:

	void HandleMovement(Player& player1, Player& player2);
	//Collision Check
	bool CheckCollisionSide(Player& player);
	//Collision Check for Top Side only
	bool CheckCollisionTop(Player& player);
};