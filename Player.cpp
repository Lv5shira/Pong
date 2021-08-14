#include "Player.h"


Player::Player()
{
	mPlayer.w = 20.0f;
	mPlayer.h = 120.0f;
	mPlayer.y = 768 / 2 - 120;

	mSpeed = 300.0f;
	mScore = 0;


	Upbounds = 133;
	Downbounds = 660;
}

void Player::AddScore()
{
	mScore++;
}

int Player::GetScore()
{
	return mScore;
}