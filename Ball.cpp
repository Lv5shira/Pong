#include "Ball.h"
#include <stdio.h>

Ball::Ball()
{
	mTimer = Timer::Instance();

	mBall.x = 1024 / 2;
	mBall.y = 768 / 2;
	mBall.w = 15;
	mBall.h = 15;

	mSpeedX = 5.0f;
	mSpeedY = 5.0f;
	Upbounds = 133;
	Downbounds = 753;
	leftBounds = -15;
	rightBounds = 1039;
}

Ball::~Ball()
{
	Timer::Release();
	mTimer = NULL;
}

void Ball::HandleMovement(Player& player1, Player& player2)
{
	mBall.x -= mSpeedX;
	mBall.y += mSpeedY;
	
	//Checks for collision Twice, If top side collision, change mSpeedY
	if (CheckCollisionSide(player1) || CheckCollisionSide(player2))
	{
		if (CheckCollisionTop(player1) || CheckCollisionTop(player2))
		{
			mSpeedY = mSpeedY * -1.0f;
			mSpeedY *= 1.1f;
			mSpeedX *= 1.1f;
		}
		mSpeedX = mSpeedX * -1.0f;
		mSpeedX *= 1.1f;
		mSpeedY *= 1.1f;
	}
	else if (mBall.y < Upbounds)
	{
		mBall.y = Upbounds;
		mSpeedY = mSpeedY * -1.0f;
	}
	else if (mBall.y > Downbounds)
	{
		mBall.y = Downbounds;
		mSpeedY = mSpeedY * -1.0f;
	}

	if (mBall.x > rightBounds)
	{
		player1.AddScore();
		mSpeedX = 5.0f;
		mSpeedY = 5.0f;
		mBall.x = 1024 / 2;
	}
	if (mBall.x < leftBounds)
	{
		player2.AddScore();
		mSpeedX = 5.0f;
		mSpeedY = 5.0f;
		mBall.x = 1024 / 2;
	}
}

//Box Box Collision

bool Ball::CheckCollisionSide(Player& player)
{
	//Sides of player1 and ball
	int leftA,  leftC;
	int rightA, rightC;
	int topA, topC;
	int bottomA, bottomC;

	//Sides for player1
	leftA = player.mPlayer.x;
	rightA = player.mPlayer.x + player.mPlayer.w;
	topA = player.mPlayer.y;
	bottomA = player.mPlayer.y + player.mPlayer.h;

	//Sides for Ball
	leftC = mBall.x;
	rightC = mBall.x + mBall.w;
	topC = mBall.y;
	bottomC = mBall.y + mBall.h;

	if (bottomA <= topC)
	{
		return false;
	}
	if (topA >= bottomC)
	{
		return false;
	}
	if (rightA <= leftC)
	{
		return false;
	}
	if (leftA >= rightC)
	{
		return false;
	}
	return true;
}

bool Ball::CheckCollisionTop(Player& player)
{
	int topA, topC;
	int bottomA, bottomC;

	topA = player.mPlayer.y;
	bottomA = player.mPlayer.y + player.mPlayer.h;

	topC = mBall.y;
	bottomC = mBall.y + mBall.h;

	if (bottomA <= topC)
	{
		return false;
	}
	if (topA >= bottomC)
	{
		return false;
	}
	return true;
}

void Ball::Update(Player& player1, Player& player2)
{
	HandleMovement(player1, player2);
}