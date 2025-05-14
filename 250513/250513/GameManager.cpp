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
	// 전투관리자 초기화
	if (!CBattleManager::GetInst()->Init())
		return false;

	return true;
}

void CGameManager::Run()
{
	while (true)
	{
		system("cls");
		printf("1. 전투\n");
		printf("2. 상점\n");
		printf("3. 가방\n");
		printf("4. 종료\n");
		printf("메뉴를 선택하세요 : ");
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
