#pragma once

#include "GameObject.h"

class CPlayer;
class CBomb :
    public CGameObject
{
public:
	CBomb();
	virtual ~CBomb();

private:
	int		mPower = 1;
	float	mFireTime = 5.f;
	CPlayer* mPlayer = nullptr;

public:
	void SetPlayer(CPlayer* Player)
	{
		mPlayer = Player;
	}

	void SetPower(int Power)
	{
		mPower = Power;
	}

	void SetFireTime(float Time)
	{
		mFireTime = Time;
	}

public:
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void Output(char* Buffer);
};

