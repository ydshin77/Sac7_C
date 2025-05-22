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
	bool Init(int StageNumber);
	void Output(char* Buffer);
};

