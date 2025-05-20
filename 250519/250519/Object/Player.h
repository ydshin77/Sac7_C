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
	int		mBombCount = 1;
	int		mBombPower = 3;

public:
	void RestoreBombCount()
	{
		++mBombCount;
	}

public:
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void Output(char* Buffer);
};

