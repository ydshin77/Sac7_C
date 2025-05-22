#pragma once

#include "Scene.h"

class CBlock;
class CSceneGame :
    public CScene
{
public:
	CSceneGame();
	virtual ~CSceneGame();

private:
	int		mStageNumber = 0;
	CBlock* mCurrentBlock = nullptr;

public:
	void SetStageNumber(int StageNumber);

public:
	virtual bool Init();
	virtual bool Begin();
	virtual void Run();

protected:
	virtual void BlockDestroy();
};

