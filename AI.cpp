#include "AI.h"

AI::AI(Player *player, Ball *ball)
{
	mTimer = Timer::Instance();
	mplayer = player;
	mBall = ball;
	mSpeed = 500.0f;
}

void AI::HandleMovement()
{
	if (mBall->mBall.y < mplayer->mPlayer.y + mplayer->mPlayer.w/2 )
	{
		mplayer->mPlayer.y -= 1.0f * mSpeed * mTimer->DeltaTime();
	}

	if (mBall->mBall.y > mplayer->mPlayer.y + mplayer->mPlayer.w / 2)
	{
		mplayer->mPlayer.y += 1.0f * mSpeed * mTimer->DeltaTime();
	}

	if (mplayer->mPlayer.y < mplayer->Upbounds)
		mplayer->mPlayer.y = mplayer->Upbounds;
	if (mplayer->mPlayer.y > mplayer->Downbounds)
		mplayer->mPlayer.y = mplayer->Downbounds;
}

void AI::Update()
{
	HandleMovement();
}