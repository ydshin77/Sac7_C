#pragma once

// ../ : 이전폴더
#include "../GameInfo.h"

class CMaze
{
public:
	CMaze();
	CMaze(const CMaze& Copy);
	~CMaze();

private:
	char	mName[32] = {};
	int		mCountX = 0;
	int		mCountY = 0;
	std::vector<ETileType>	mTileList;
	std::vector<char>		mTileOutputList;
	COORD	mStartPos;
	COORD	mExitPos;

public:
	const COORD& GetStartPos()	const
	{
		return mStartPos;
	}

	const COORD& GetExitPos()	const
	{
		return mExitPos;
	}

	const char* GetName()	const
	{
		return mName;
	}

	int GetCountX()	const
	{
		return mCountX;
	}

	int GetCountY()	const
	{
		return mCountY;
	}

	int GetCount()	const
	{
		return (int)mTileList.size();
	}

	int GetOutputCount()	const
	{
		return (int)mTileOutputList.size();
	}

	ETileType GetTileType(const COORD& Pos);
	void SetTileType(ETileType Type, const COORD& Pos);

public:
	bool Init(const char* FileName);
	void Output(char* Buffer);
	CMaze* Clone();
};

