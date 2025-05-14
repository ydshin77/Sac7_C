#include "Store.h"
#include "ObjectManager.h"
#include "Item.h"
#include "Player.h"

CStore::CStore()
{
}

CStore::~CStore()
{
}

bool CStore::Init(EStoreType::Type StoreType)
{
    mStoreType = StoreType;

    CObjectManager::GetInst()->AddStoreItem(mItemList, StoreType);

    return true;
}

void CStore::Run()
{
    CPlayer* Player = CObjectManager::GetInst()->GetPlayer();

    while (true)
    {
        system("cls");

        switch (mStoreType)
        {
        case EStoreType::Weapon:
            printf("============== ������� ==============\n");
            break;
        case EStoreType::Armor:
            printf("============== ������ ==============\n");
            break;
        }

        int Size = mItemList.size();

        for (int i = 0; i < Size; ++i)
        {
            printf("%d. %s\n", i + 1, mItemList[i]->GetName());
        }

        printf("%d. �ڷΰ���\n", Size + 1);

        printf("������� : %d\n", Player->GetGold());
        printf("������ �������� �����ϼ��� : ");
        int	Input = 0;
        scanf_s("%d", &Input);

        if (Input <= 0 || Input > Size + 1)
            continue;

        else if (Input == Size + 1)
            return;

        // ������ ������ ��ȣ�� ������ �ε����� �����Ѵ�.
        int	StoreIndex = Input - 1;

        // �÷��̾ ������ �ݾ��� �������� üũ�Ѵ�.
        if (Player->GetGold() < mItemList[StoreIndex]->GetPrice())
        {
            printf("�����ݾ��� �����մϴ�.\n");
            system("pause");
            continue;
        }

        // �κ��丮 ĭ �������� üũ


        // ������ ����
        CItem* NewItem = mItemList[StoreIndex]->Clone();

        // �κ��丮�� �߰�

        // �÷��̾� �������� ����.
        Player->AddGold(-mItemList[StoreIndex]->GetPrice());
    }
}
