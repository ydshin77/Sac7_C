#pragma once

#include "Scene.h"

class CPlayer;
class CSceneGame :
    public CScene
{
public:
	CSceneGame();
	virtual ~CSceneGame();

private:
	COORD	mStartPos;
	COORD	mExitPos;
	CPlayer* mPlayer = nullptr;

public:
	virtual void SetMaze(CMaze* Maze);

public:
	virtual bool Init();
	virtual void Run();
};

