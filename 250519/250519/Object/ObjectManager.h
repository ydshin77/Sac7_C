#pragma once

#include "../GameInfo.h"

class CObjectManager
{
private:
	CObjectManager();
	~CObjectManager();

public:
	bool Init();

private:
	static CObjectManager* mInst;

public:
	static CObjectManager* GetInst();
	static void DestroyInst();
};

