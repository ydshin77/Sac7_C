#pragma once

#include "../GameInfo.h"

class CStage
{
public:
	CStage();
	~CStage();

private:
	int		mStageNumber = 0;
	std::vector<EBlockType>	mBlockList;
	std::vector<char>		mBlockOutputList;

public:
	EBlockType GetBlock(const COORD& Pos);
	EBlockType GetBlock(int x, int y);
	void SetBlock(EBlockType Type, const COORD& Pos);
	void SetBlock(EBlockType Type, int x, int y);
	void LineDrop(int y);
	void ClearLine(int y);

public:
	bool Init(int StageNumber);
	void Output(char* Buffer);
};

