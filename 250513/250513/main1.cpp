
#include "GameManager.h"

int main()
{
	// CGameManager::GetInst()�� �ϸ� ��ü�� �����ϰ� -> �� �̿��� ������ ��ü��
	// ����� ������ �� �ִ�.
	if (!CGameManager::GetInst()->Init())
	{
		CGameManager::DestroyInst();
		return 0;
	}

	CGameManager::GetInst()->Run();

	CGameManager::DestroyInst();

	return 0;
}
