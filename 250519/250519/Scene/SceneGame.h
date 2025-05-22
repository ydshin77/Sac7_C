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
	// map은 key, value 2가지 타입으로 구성된다.
	// key는 탐색을 위한 타입이다.
	// value는 실제 저장하고자 하는 타입이다.
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

