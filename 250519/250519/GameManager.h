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

private:
	void RunGame(int MazeIndex);

public:
	void Run();

private:
	static CGameManager* mInst;

public:
	static CGameManager* GetInst();
	static void DestroyInst();
};

