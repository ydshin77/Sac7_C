
#include "Inventory.h"

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

FInventory* gInventory = nullptr;

float	gUpgradeRate[ITEM_UPGRADE_MAX] =
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

void OutputItem(const FItem* Item)
{
	if (!Item)
	{
		printf("없음\n");
	}

	else
	{
		//printf("이름 : %s\t종류 : ", Item->Name);
		printf("이름 : %s", Item->Name);

		if (Item->Upgrade > 0)
			printf(" + %d", Item->Upgrade);

		printf("\t종류 : ");

		switch (Item->ItemType)
		{
		case EItemType::Weapon:
			printf("무기\n");
			printf("공격력 : %d\n", Item->Option);
			break;
		case EItemType::Armor:
			printf("방어구\n");
			printf("방어력 : %d\n", Item->Option);
			break;
		}

		printf("상점구매가격 : %d\t상점판매가격 : %d\n",
			Item->Price, Item->Sell);
	}
}

void Equip(int ItemIndex)
{
	// 아이템 타입을 이용하여 장착부위를 구한다.
	EEquip::Type	EquipType = EEquip::None;

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
		printf("장착할 수 없는 아이템입니다.\n");
		system("pause");
		return;
	}

	// 플레이어에 아이템을 장착한다.
	// 플레이어가 장착하고 있던 아이템을 받아온다.
	FItem* EquipItem = gPlayer->EquipItem[EquipType];

	// 아이템을 장착한다.
	gPlayer->EquipItem[EquipType] = gInventory->ItemList[ItemIndex];

	// 인벤토리에 장착하고 있던 아이템을 넣어준다.
	gInventory->ItemList[ItemIndex] = EquipItem;

	// 기존에 장착하고 있던 아이템이 없을 경우 아이템 수를 줄여준다.
	if (!EquipItem)
		--gInventory->Count;
}

void Upgrade(int ItemIndex)
{
	// 돈이 부족한지 체크한다.
	if (gPlayer->Gold < 1000)
	{
		printf("보유금액이 부족합니다.\n");
		system("pause");
		return;
	}

	// 선택한 아이템의 강화 등급이 최대치인지 확인한다.
	else if (gInventory->ItemList[ItemIndex]->Upgrade ==
		ITEM_UPGRADE_MAX)
	{
		printf("선택한 아이템의 강화 수치가 최대입니다.\n");
		system("pause");
		return;
	}

	// 돈을 차감한다.
	gPlayer->Gold -= 1000;

	// 선택한 아이템의 강화 등급에 맞는 확률을 가져온다.
	float Rate = gUpgradeRate[gInventory->ItemList[ItemIndex]->Upgrade];

	float Percent = rand() % 10000 / 100.f;

	if (Percent < Rate)
	{
		printf("강화 성공\n");
		++gInventory->ItemList[ItemIndex]->Upgrade;

		gInventory->ItemList[ItemIndex]->Option =
			(int)(gInventory->ItemList[ItemIndex]->Option * 1.1f);
		gInventory->ItemList[ItemIndex]->Sell =
			(int)(gInventory->ItemList[ItemIndex]->Sell * 1.1f);
	}

	else
	{
		printf("강화실패\n");
	}

	system("pause");
}

void ItemSell(int ItemIndex)
{
	// 아이템이 없을 경우
	if (!gInventory->ItemList[ItemIndex])
	{
		printf("판매할 아이템이 없습니다.\n");
		system("pause");
		return;
	}

	// 플레이어 보유금액을 증가시킨다.
	gPlayer->Gold += gInventory->ItemList[ItemIndex]->Sell;

	// 아이템을 제거한다.
	SAFE_DELETE(gInventory->ItemList[ItemIndex]);

	--gInventory->Count;
}

void RunItem(int ItemIndex)
{
	while (true)
	{
		system("cls");

		OutputItem(gInventory->ItemList[ItemIndex]);
		printf("\n");

		printf("1. 장착\n");
		printf("2. 강화\n");
		printf("3. 판매\n");
		printf("4. 뒤로가기\n");
		printf("메뉴를 선택하세요 : ");
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
			ItemSell(ItemIndex);
			return;
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

		printf("0. 뒤로가기\n");

		// 장착아이템 및 보유골드 출력
		printf("장착무기 : ");

		if (gPlayer->EquipItem[EEquip::Weapon])
		{
			printf("%s", gPlayer->EquipItem[EEquip::Weapon]->Name);

			if (gPlayer->EquipItem[EEquip::Weapon]->Upgrade > 0)
				printf(" + %d", gPlayer->EquipItem[EEquip::Weapon]->Upgrade);

			printf("\t");
		}

		else
			printf("없음\t");

		printf("장착방어구 : ");

		if (gPlayer->EquipItem[EEquip::Armor])
		{
			printf("%s\n", gPlayer->EquipItem[EEquip::Armor]->Name);

			if (gPlayer->EquipItem[EEquip::Armor]->Upgrade > 0)
				printf(" + %d", gPlayer->EquipItem[EEquip::Armor]->Upgrade);

			printf("\t");
		}

		else
			printf("없음\n");

		printf("보유골드 : %d\n", gPlayer->Gold);

		printf("아이템을 선택하세요 : ");
		int	Input = 0;
		scanf_s("%d", &Input);

		if (Input == 0)
			break;

		else if (Input < 0 || Input > INVENTORY_MAX)
			continue;

		RunItem(Input - 1);
	}
}
