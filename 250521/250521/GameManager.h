#pragma once

#include "GameInfo.h"

class CGameManager
{
private:
	CGameManager();
	~CGameManager();

private:
	bool	mLoop = true;

public:
	void Exit()
	{
		mLoop = false;
	}

public:
	bool Init();

public:
	void Run();

private:
	static CGameManager* mInst;

public:
	static CGameManager* GetInst();
	static void DestroyInst();
};

