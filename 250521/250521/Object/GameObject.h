#pragma once

#include "../GameInfo.h"

class CScene;
class CGameObject
{
public:
	CGameObject();
	virtual ~CGameObject();

protected:
	CScene* mScene = nullptr;
	COORD		mPos = { 0, 0 };
	bool		mActive = true;

public:
	void SetScene(CScene* Scene)
	{
		mScene = Scene;
	}

	bool GetActive()	const
	{
		return mActive;
	}

	void Destroy()
	{
		mActive = false;
	}

	void SetPos(int x, int y)
	{
		mPos.X = x;
		mPos.Y = y;
	}

	void SetPos(const COORD& Pos)
	{
		mPos = Pos;
	}

	const COORD& GetPos()	const
	{
		return mPos;
	}

public:
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void Output(char* OutputBuffer);
};

