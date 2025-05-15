#include "Inventory.h"
#include "Item.h"
#include "Player.h"
#include "ObjectManager.h"

namespace EInventoryMenu
{
    enum Type
    {
        None,
        Equip,
        Upgrade,
        Sell,
        Back,
        End
    };
}

CInventory* CInventory::mInst = nullptr;

CInventory::CInventory()
{
}

CInventory::~CInventory()
{
    for (int i = 0; i < mItemMaxCount; ++i)
    {
        SAFE_DELETE(mItemList[i]);
    }
}

void CInventory::AddItem(CItem* Item)
{
    for (int i = 0; i < mItemMaxCount; ++i)
    {
        // ����ִ� ������ ã�Ƽ� �������� �߰��Ѵ�.
        if (!mItemList[i])
        {
            mItemList[i] = Item;
            ++mItemCount;
            break;
        }
    }
}

bool CInventory::Init()
{
    // �κ��丮 ��ü ������ŭ nullptr�� �̸� ä���д�.
    for (int i = 0; i < mItemMaxCount; ++i)
    {
        mItemList.push_back(nullptr);
    }

    return true;
}

void CInventory::Equip(int ItemIndex)
{
    // ������ Ÿ���� �̿��Ͽ� ���������� ���Ѵ�.
    EEquip::Type	EquipType = EEquip::None;

    switch (mItemList[ItemIndex]->GetItemType())
    {
    case EItemType::Weapon:
        EquipType = EEquip::Weapon;
        break;
    case EItemType::Armor:
        EquipType = EEquip::Armor;
        break;
    }

    if (EquipType == EEquip::None)
    {
        printf("������ �� ���� �������Դϴ�.\n");
        system("pause");
        return;
    }

    CPlayer* Player = CObjectManager::GetInst()->GetPlayer();

    // �÷��̾ �������� �����Ѵ�.
    // �÷��̾ �����ϰ� �ִ� �������� �޾ƿ´�.
    CItem* EquipItem = Player->Equip(EquipType, mItemList[ItemIndex]);

    // �κ��丮�� �����ϰ� �ִ� �������� �־��ش�.
    mItemList[ItemIndex] = EquipItem;

    // ������ �����ϰ� �ִ� �������� ���� ��� ������ ���� �ٿ��ش�.
    if (!EquipItem)
        --mItemCount;
}

void CInventory::Upgrade(int ItemIndex)
{
    CPlayer* Player = CObjectManager::GetInst()->GetPlayer();

    // ���� �������� üũ�Ѵ�.
    if (Player->GetGold() < 1000)
    {
        printf("�����ݾ��� �����մϴ�.\n");
        system("pause");
        return;
    }

    // ������ �������� ��ȭ ����� �ִ�ġ���� Ȯ���Ѵ�.
    else if (mItemList[ItemIndex]->GetUpgrade() ==
        ITEM_UPGRADE_MAX)
    {
        printf("������ �������� ��ȭ ��ġ�� �ִ��Դϴ�.\n");
        system("pause");
        return;
    }

    // ���� �����Ѵ�.
    Player->AddGold(-1000);

    // ������ �������� ��ȭ ��޿� �´� Ȯ���� �����´�.
    float Rate = mUpgradeRate[mItemList[ItemIndex]->GetUpgrade()];

    float Percent = rand() % 10000 / 100.f;

    if (Percent < Rate)
    {
        printf("��ȭ ����\n");

        int AddOption = (int)(mItemList[ItemIndex]->GetOption() * 0.1f);
        int AddSell = (int)(mItemList[ItemIndex]->GetSell() * 0.1f);

        mItemList[ItemIndex]->UpgradeSuccess(1, AddOption, AddSell);
    }

    else
    {
        printf("��ȭ����\n");
    }

    system("pause");
}

void CInventory::Sell(int ItemIndex)
{
    // �������� ���� ���
    if (!mItemList[ItemIndex])
    {
        printf("�Ǹ��� �������� �����ϴ�.\n");
        system("pause");
        return;
    }

    CPlayer* Player = CObjectManager::GetInst()->GetPlayer();

    // �÷��̾� �����ݾ��� ������Ų��.
    Player->AddGold(mItemList[ItemIndex]->GetSell());

    // �������� �����Ѵ�.
    SAFE_DELETE(mItemList[ItemIndex]);

    --mItemCount;
}

void CInventory::RunItem(int ItemIndex)
{
    if (!mItemList[ItemIndex])
        return;

    while (true)
    {
        system("cls");

        mItemList[ItemIndex]->Output();
        printf("\n");

        printf("1. ����\n");
        printf("2. ��ȭ\n");
        printf("3. �Ǹ�\n");
        printf("4. �ڷΰ���\n");
        printf("�޴��� �����ϼ��� : ");
        int	Input = 0;
        scanf_s("%d", &Input);

        if (Input <= EInventoryMenu::None ||
            Input >= EInventoryMenu::End)
            continue;

        else if (Input == EInventoryMenu::Back)
            break;

        switch (Input)
        {
        case EInventoryMenu::Equip:
            Equip(ItemIndex);
            return;
        case EInventoryMenu::Upgrade:
            Upgrade(ItemIndex);
            break;
        case EInventoryMenu::Sell:
            Sell(ItemIndex);
            return;
        }
    }
}

void CInventory::Run()
{
    CPlayer* Player = CObjectManager::GetInst()->GetPlayer();

    while (true)
    {
        system("cls");

        for (int i = 0; i < mItemMaxCount; ++i)
        {
            printf("%d. ", i + 1);

            if (mItemList[i])
                mItemList[i]->Output();

            else
                printf("����\n");
        }

        printf("0. �ڷΰ���\n");

        // ���������� �� ������� ���
        printf("�������� : ");

        if (Player->GetEquipItem(EEquip::Weapon))
        {
            printf("%s", Player->GetEquipItem(EEquip::Weapon)->GetName());

            if (Player->GetEquipItem(EEquip::Weapon)->GetUpgrade() > 0)
                printf(" + %d", Player->GetEquipItem(EEquip::Weapon)->GetUpgrade());

            printf("\t");
        }

        else
            printf("����\t");

        printf("������ : ");

        if (Player->GetEquipItem(EEquip::Armor))
        {
            printf("%s\n", Player->GetEquipItem(EEquip::Armor)->GetName());

            if (Player->GetEquipItem(EEquip::Armor)->GetUpgrade() > 0)
                printf(" + %d", Player->GetEquipItem(EEquip::Armor)->GetUpgrade());

            printf("\t");
        }

        else
            printf("����\n");

        printf("������� : %d\n", Player->GetGold());

        printf("�������� �����ϼ��� : ");
        int	Input = 0;
        scanf_s("%d", &Input);

        if (Input == 0)
            break;

        else if (Input < 0 || Input > mItemMaxCount)
            continue;

        RunItem(Input - 1);
    }
}

CInventory* CInventory::GetInst()
{
    if (!mInst)
        mInst = new CInventory;

    return mInst;
}

void CInventory::DestroyInst()
{
    SAFE_DELETE(mInst);
}
