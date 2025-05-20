#pragma once

#include "Scene.h"

class CSceneGame :
    public CScene
{
public:
	CSceneGame();
	virtual ~CSceneGame();

public:
	virtual bool Init();
	virtual void Run();
};

