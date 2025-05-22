#pragma once

#include "Scene.h"

class CPlayer;
class CSceneGame :
    public CScene
{
public:
	CSceneGame();
	virtual ~CSceneGame();

private:
	// map�� key, value 2���� Ÿ������ �����ȴ�.
	// key�� Ž���� ���� Ÿ���̴�.
	// value�� ���� �����ϰ��� �ϴ� Ÿ���̴�.
	std::unordered_map<int, class CTrap*>	mTrapMap;
	COORD	mStartPos;
	COORD	mExitPos;
	CPlayer* mPlayer = nullptr;
	int		mScore = 0;

public:
	class CTrap* FindTrap(int Index);
	void EraseTrap(int Index);

public:
	virtual void SetMaze(CMaze* Maze);

public:
	virtual bool Init();
	virtual void Run();
};

