#pragma once

#include "../GameInfo.h"

class CStage;
class CScene
{
public:
	CScene();
	virtual ~CScene();

protected:
	CStage* mStage = nullptr;

public:
	virtual bool Init();
	virtual bool Begin();
	virtual void Run();

private:
	void Update();
	void Output();
};

