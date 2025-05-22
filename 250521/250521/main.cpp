// 테트리스 게임

#include "GameManager.h"

int main()
{
	srand(time(0));
	rand();

	if (!CGameManager::GetInst()->Init())
	{
		CGameManager::DestroyInst();
		return 0;
	}

	CGameManager::GetInst()->Run();

	CGameManager::DestroyInst();

	return 0;
}