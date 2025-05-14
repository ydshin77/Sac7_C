#include "BattleManager.h"
#include "Battle.h"

CBattleManager* CBattleManager::mInst = nullptr;

CBattleManager::CBattleManager()
{
}

CBattleManager::~CBattleManager()
{
}

bool CBattleManager::Init()
{
	return true;
}

void CBattleManager::Run()
{
	while (true)
	{
		// ���� �޴��� �����ְ� �����Ѵ�.
		system("cls");
		printf("1. ����\n");
		printf("2. ����\n");
		printf("3. �����\n");
		printf("4. �ڷΰ���\n");
		printf("�޴��� �����ϼ��� : ");
		int	Input = 0;
		scanf_s("%d", &Input);

		switch ((EMapMenu)Input)
		{
		case EMapMenu::Easy:
		case EMapMenu::Normal:
		case EMapMenu::Hard:
			mBattle = new CBattle;

			mBattle->Init((EMapMenu)Input);

			mBattle->Run();

			SAFE_DELETE(mBattle);
			break;
		case EMapMenu::Back:
			return;
		}
	}
}

CBattleManager* CBattleManager::GetInst()
{
	if (!mInst)
		mInst = new CBattleManager;

	return mInst;
}

void CBattleManager::DestroyInst()
{
	SAFE_DELETE(mInst);
}
