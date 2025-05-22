#pragma once

#include "GameObject.h"

class CPlayer	:
	public CGameObject
{
public:
	CPlayer();
	virtual ~CPlayer();

private:
	float	mPosX = 0.f;
	float	mPosY = 0.f;
	float	mMoveSpeed = 5.f;
	int		mBombCount = 0;
	int		mBombCountMax = 1;
	int		mBombPower = 1;

public:
	void RestoreBombCount()
	{
		--mBombCount;

		if (mBombCount < 0)
			mBombCount = 0;
	}

	void CountUp()
	{
		++mBombCountMax;

		if (mBombCountMax > 5)
			mBombCountMax = 5;
	}

	void PowerUp()
	{
		++mBombPower;

		if (mBombPower > 5)
			mBombPower = 5;
	}

	void MoveSpeedUp()
	{
		mMoveSpeed += 0.5f;

		if (mMoveSpeed > 10.f)
			mMoveSpeed = 10.f;
	}

public:
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void Output(char* Buffer);
};

