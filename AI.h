#pragma once
#include "Ball.h"

class AI
{
private:

	Player* mplayer;
	Ball* mBall;
	Timer* mTimer;
	float mSpeed;

public:

	AI(Player *player, Ball *ball);
	~AI();

	void HandleMovement();

	void Update();
};