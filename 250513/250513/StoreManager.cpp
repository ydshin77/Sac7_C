#include "StoreManager.h"
#include "Store.h"

CStoreManager* CStoreManager::mInst = nullptr;

CStoreManager::CStoreManager()
{
}

CStoreManager::~CStoreManager()
{
}

bool CStoreManager::Init()
{
    return true;
}

void CStoreManager::Run()
{
    while (true)
    {
		system("cls");
		printf("1. �������\n");
		printf("2. ������\n");
		printf("3. �ڷΰ���\n");
		printf("������ �����ϼ��� : ");
		int	Input = 0;
		scanf_s("%d", &Input);

		if (Input <= EStoreType::None || Input >= EStoreType::End)
			continue;

		switch (Input)
		{
		case EStoreType::Weapon:
		case EStoreType::Armor:
		{
			CStore	Store;

			Store.Init((EStoreType::Type)Input);

			Store.Run();
		}
			break;
		case EStoreType::Back:
			return;
		}
    }
}

CStoreManager* CStoreManager::GetInst()
{
    if (!mInst)
        mInst = new CStoreManager;

    return mInst;
}

void CStoreManager::DestroyInst()
{
    SAFE_DELETE(mInst);
}
