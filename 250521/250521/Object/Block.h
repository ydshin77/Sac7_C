#pragma once

#include "GameObject.h"

class CBlock :
	public CGameObject
{
public:
	CBlock();
	virtual ~CBlock();

protected:
	char	mBlock[16] = {};
	int		mBlockIndex[4] = {};
	int		mSideIndexMin = 0;
	int		mSideIndexMax = 0;
	int		mFloorIndex = 0;
	float	mPosX = 0.f;
	float	mPosY = 0.f;
	float	mSideSpeed = 6.f;
	float	mDownSpeed = 3.f;

public:
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void Output(char* OutputBuffer);

private:
	void ChagneBlock();
	void ClearLine();
};

