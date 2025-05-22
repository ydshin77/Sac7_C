#pragma once

#include "Scene.h"

class CSceneGame :
	public CScene
{
public:
	CSceneGame();
	virtual ~CSceneGame();

private:
	int		mStageNumber = 0;

public:
	void SetStageNumber(int StageNumber);

public:
	virtual bool Init();
	virtual bool Begin();
	virtual void Run();
};

