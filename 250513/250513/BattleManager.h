#pragma once

#include "GameInfo.h"

// ���漱�� : �� Ŭ������ ��򰡿� �ִٰ� �����ϰ� ������ ������ ����� �� �ְ�
// ������ش�. ���� ��� �κп����� include�� ���־�� �Ѵ�.
class CBattle;
class CBattleManager
{
private:
	CBattleManager();
	~CBattleManager();

private:
	CBattle* mBattle = nullptr;

public:
	bool Init();
	void Run();

private:
	static CBattleManager* mInst;

public:
	static CBattleManager* GetInst();
	static void DestroyInst();
};

