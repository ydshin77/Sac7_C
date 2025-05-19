
#include "Inventory.h"

namespace EInventoryItemMenu
{
	enum Type
	{
		None,
		Equip,
		Upgrade,
		Back,
		End
	};
}

// �κ��丮�� ���� ������ ����
FInventory* gInventory = nullptr;

// ��ȭ Ȯ��
float gUpgradeRate[ITEM_UPGRADE_MAX] =
{
	100.f, 100.f, 100.f, 90.f, 85.f, 80.f, 75.f, 70.f, 65.f, 60.f,
	20.f, 15.f, 10.f, 5.f, 1.f, 0.5f, 0.3f, 0.1f, 0.07f, 0.05f
};

bool InventoryInit()
{
	gInventory = new FInventory;

	return true;
}

void InventoryDestroy()
{
	for (int i = 0; i < INVENTORY_MAX; ++i)
	{
		SAFE_DELETE(gInventory->ItemList[i]);
	}

	SAFE_DELETE(gInventory);
}

// ������ ���� ���
// Item ���� ��¸� �� �Ŵϱ� const �Է� (�� ���� �Ұ�, �ּ� ���� ����)
void OutputItem(const FItem* Item)
{
	if (!Item)
	{
		printf("����\n");
	}
	
	else
	{
		printf("�̸� : %s", Item->Name);

		if (Item->Upgrade > 0)
			printf(" + %d", Item->Upgrade);

		printf("\t���� : ");

		switch (Item->ItemType)
		{
		case EItemType::Weapon:
			printf("����\n");
			printf("���ݷ� : %d\n", Item->Option);
			break;
		case EItemType::Armor:
			printf("��\n");
			printf("���� : %d\n", Item->Option);
			break;
		}

		printf("���� ���� ���� : %d\t ���� �Ǹ� ����: %d\n", Item->Price, Item->Sell);
	}
}

// ������ ������ ����
void Equip(int ItemIndex)
{
	// ������ Ÿ���� �̿��Ͽ� ���� ������ ����
	EEquip::Type EquipType = EEquip::None;

	switch (gInventory->ItemList[ItemIndex]->ItemType)
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

	// �÷��̾ ������ ����
	// �÷��̾ �����ϰ� �ִ� �������� �޾ƿ�
	FItem* EquipItem = gPlayer->EquipItem[EquipType];

	// ������ ����
	gPlayer->EquipItem[EquipType] = gInventory->ItemList[ItemIndex];

	// �κ��丮�� �����ϰ� �ִ� �������� �־��� (����)
	gInventory->ItemList[ItemIndex] = EquipItem;
}

// ������ ������ ��ȭ
void Upgrade(int ItemIndex)
{
	// ���� �������� üũ
	if (gPlayer->Gold < 1000)
	{
		printf("���� �ݾ��� �����մϴ�.\n");
		system("pause");
		return;
	}

	// ������ �������� ��ȭ ����� �ִ�ġ���� Ȯ��
	else if (gInventory->ItemList[ItemIndex]->Upgrade == ITEM_UPGRADE_MAX)
	{
		printf("������ �������� ��ȭ ��ġ�� �ִ��Դϴ�.\n");
		system("pause");
		return;
	}

	// �� ����
	gPlayer->Gold -= 1000;

	// ������ �������� ��ȭ ��޿� �´� Ȯ���� ������
	float Rate = gUpgradeRate[gInventory->ItemList[ItemIndex]->Upgrade];

	float Percent = rand() % 10000 / 100.f;

	if (Percent < Rate)
	{
		printf("��ȭ ����\n");
		++gInventory->ItemList[ItemIndex]->Upgrade;

		gInventory->ItemList[ItemIndex]->Option =
			(int)(gInventory->ItemList[ItemIndex]->Option * 1.1f);

		gInventory->ItemList[ItemIndex]->Sell =
			(int)(gInventory->ItemList[ItemIndex]->Sell * 1.1f);
	}

	else
		printf("��ȭ ����\n");

	system("pause");
}

// ������ ������ �޴� ���
void RunItem(int ItemIndex)
{
	while (true)
	{
		system("cls");

		OutputItem(gInventory->ItemList[ItemIndex]);
		printf("\n");

		printf("1. ����\n");
		printf("2. ��ȭ\n");
		printf("3. �ڷΰ���\n");

		// ���� ������ �� ���� ��� ���
		printf("���� ���� : ");
		if (gPlayer->EquipItem[EEquip::Weapon])
		{
			printf("%s", gPlayer->EquipItem[EEquip::Weapon]->Name);

			if (gPlayer->EquipItem[EEquip::Weapon]->Upgrade > 0)
				printf(" +%d", gPlayer->EquipItem[EEquip::Weapon]->Upgrade);

			printf("\t");
		}

		else
			printf("����\t");

		printf("���� �� : ");
		if (gPlayer->EquipItem[EEquip::Armor])
		{
			printf("%s", gPlayer->EquipItem[EEquip::Armor]->Name);

			if (gPlayer->EquipItem[EEquip::Armor]->Upgrade > 0)
				printf(" +%d", gPlayer->EquipItem[EEquip::Armor]->Upgrade);

			printf("\n");
		}

		else
			printf("����\n");

		printf("���� ��� : %d\n", gPlayer->Gold);

		printf("�޴��� �����ϼ��� : ");
		int Input = 0;
		scanf_s("%d", &Input);

		if (Input <= EInventoryItemMenu::None || Input >= EInventoryItemMenu::End)
		{
			printf("�߸��� ���� �Է��Ͽ����ϴ�. �ٽ� �Է����ּ���.\n");
			system("pause");
			continue;
		}

		else if (Input == EInventoryItemMenu::Back)
			break;

		switch (Input)
		{
		case EInventoryItemMenu::Equip:
			Equip(ItemIndex);
			return;
		case EInventoryItemMenu::Upgrade:
			Upgrade(ItemIndex);
			break;
		}
	}
}

void RunInventory()
{
	while (true)
	{
		system("cls");

		for (int i = 0; i < INVENTORY_MAX; ++i)
		{
			printf("%d. ", i + 1);
			OutputItem(gInventory->ItemList[i]);
		}

		printf("0. �ڷ� ����\n");

		printf("�������� �����ϼ��� : ");
		int Input = 0;
		scanf_s("%d", &Input);

		if (Input == 0)
		{
			printf("������ �����մϴ�.");
			break;
		}

		else if (Input < 0 || Input > INVENTORY_MAX)
		{
			printf("�߸��� ���� �Է��Ͽ����ϴ�. �ٽ� �Է����ּ���.\n");
			system("pause");
			continue;
		}

		RunItem(Input - 1);
	}
}
