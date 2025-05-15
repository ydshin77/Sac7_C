#include "GameManager.h"
#include "BattleManager.h"
#include "ObjectManager.h"
#include "StoreManager.h"
#include "Inventory.h"

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
	CInventory::DestroyInst();

	CStoreManager::DestroyInst();

	CObjectManager::DestroyInst();

	CBattleManager::DestroyInst();
}

bool CGameManager::Init()
{
	// ���������� �ʱ�ȭ
	if (!CBattleManager::GetInst()->Init())
		return false;

	// ������Ʈ ������ �ʱ�ȭ
	if (!CObjectManager::GetInst()->Init())
		return false;

	// ���� ������ �ʱ�ȭ
	if (!CStoreManager::GetInst()->Init())
		return false;

	// �κ��丮 �ʱ�ȭ
	if (!CInventory::GetInst()->Init())
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
			CStoreManager::GetInst()->Run();
			break;
		case EMainMenu::Inventory:
			CInventory::GetInst()->Run();
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
