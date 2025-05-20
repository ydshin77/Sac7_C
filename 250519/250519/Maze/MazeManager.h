#pragma once

#include "../GameInfo.h"

class CMaze;
class CMazeManager
{
private:
	CMazeManager();
	~CMazeManager();

private:
	std::vector<CMaze*>	mMazeList;

public:
	CMaze* CloneMaze(int Index);

	int GetMazeCount()	const
	{
		return (int)mMazeList.size();
	}


	int GetTileCount(int Index)	const;
	int GetTileOutputCount(int Index)	const;
	int GetCountY(int Index)	const;

public:
	bool Init();
	int OutputMenu();
	void OutputMaze(int Index, char* Buffer);

private:
	static CMazeManager* mInst;

public:
	static CMazeManager* GetInst();
	static void DestroyInst();
};

