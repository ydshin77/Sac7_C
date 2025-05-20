#pragma once

#include "../GameInfo.h"

class CGameObject
{
public:
	CGameObject();
	virtual ~CGameObject();

protected:
	int		mPosX = 0;
	int		mPosY = 0;

public:
	void SetPos(int x, int y)
	{
		mPosX = x;
		mPosY = y;
	}

public:
	virtual bool Init();
	virtual void Output();
};

