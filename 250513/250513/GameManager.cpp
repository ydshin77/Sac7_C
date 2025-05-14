#include "GameManager.h"
#include "BattleManager.h"

enum class EMainMenu : unsigned char
{
	None,
	Battle,
	Store,
	Inventory,
	Exit,
	End
};

CGameManager* CGameManager::mInst = nullptr;

CGameManager::CGameManager()
{
}

CGameManager::~CGameManager()
{
	CBattleManager::DestroyInst();
}

bool CGameManager::Init()
{
	// ���������� �ʱ�ȭ
	if (!CBattleManager::GetInst()->Init())
		return false;

	return true;
}

void CGameManager::Run()
{
	while (true)
	{
		system("cls");
		printf("1. ����\n");
		printf("2. ����\n");
		printf("3. ����\n");
		printf("4. ����\n");
		printf("�޴��� �����ϼ��� : ");
		int	Input = 0;
		scanf_s("%d", &Input);

		switch ((EMainMenu)Input)
		{
		case EMainMenu::Battle:
			CBattleManager::GetInst()->Run();
			break;
		case EMainMenu::Store:
			break;
		case EMainMenu::Inventory:
			break;
		case EMainMenu::Exit:
			return;
		}
	}
}

CGameManager* CGameManager::GetInst()
{
	if (!mInst)
		mInst = new CGameManager;

	return mInst;
}

void CGameManager::DestroyInst()
{
	SAFE_DELETE(mInst);
}
