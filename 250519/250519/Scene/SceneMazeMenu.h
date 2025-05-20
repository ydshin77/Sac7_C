#pragma once

#include "Scene.h"

class CSceneMazeMenu :
    public CScene
{
public:
	CSceneMazeMenu();
	virtual ~CSceneMazeMenu();

public:
	virtual bool Init();
	virtual void Run();
};

