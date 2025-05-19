
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

// 인벤토리를 전역 변수로 선언
FInventory* gInventory = nullptr;

// 강화 확률
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

// 아이템 정보 출력
// Item 값을 출력만 할 거니까 const 입력 (값 변경 불가, 주소 변경 가능)
void OutputItem(const FItem* Item)
{
	if (!Item)
	{
		printf("없음\n");
	}
	
	else
	{
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

		printf("상점 구매 가격 : %d\t 상점 판매 가격: %d\n", Item->Price, Item->Sell);
	}
}

// 선택한 아이템 장착
void Equip(int ItemIndex)
{
	// 아이템 타입을 이용하여 장착 부위를 구함
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
		printf("장착할 수 없는 아이템입니다.\n");
		system("pause");
		return;
	}

	// 플레이어에 아이템 장착
	// 플레이어가 장착하고 있던 아이템을 받아옴
	FItem* EquipItem = gPlayer->EquipItem[EquipType];

	// 아이템 장착
	gPlayer->EquipItem[EquipType] = gInventory->ItemList[ItemIndex];

	// 인벤토리에 장착하고 있던 아이템을 넣어줌 (스왑)
	gInventory->ItemList[ItemIndex] = EquipItem;
}

// 선택한 아이템 강화
void Upgrade(int ItemIndex)
{
	// 돈이 부족한지 체크
	if (gPlayer->Gold < 1000)
	{
		printf("보유 금액이 부족합니다.\n");
		system("pause");
		return;
	}

	// 선택한 아이템의 강화 등급이 최대치인지 확인
	else if (gInventory->ItemList[ItemIndex]->Upgrade == ITEM_UPGRADE_MAX)
	{
		printf("선택한 아이템의 강화 수치가 최대입니다.\n");
		system("pause");
		return;
	}

	// 돈 차감
	gPlayer->Gold -= 1000;

	// 선택한 아이템의 강화 등급에 맞는 확률을 가져옴
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
		printf("강화 실패\n");

	system("pause");
}

// 선택한 아이템 메뉴 출력
void RunItem(int ItemIndex)
{
	while (true)
	{
		system("cls");

		OutputItem(gInventory->ItemList[ItemIndex]);
		printf("\n");

		printf("1. 장착\n");
		printf("2. 강화\n");
		printf("3. 뒤로가기\n");

		// 장착 아이템 및 보유 골드 출력
		printf("장착 무기 : ");
		if (gPlayer->EquipItem[EEquip::Weapon])
		{
			printf("%s", gPlayer->EquipItem[EEquip::Weapon]->Name);

			if (gPlayer->EquipItem[EEquip::Weapon]->Upgrade > 0)
				printf(" +%d", gPlayer->EquipItem[EEquip::Weapon]->Upgrade);

			printf("\t");
		}

		else
			printf("없음\t");

		printf("장착 방어구 : ");
		if (gPlayer->EquipItem[EEquip::Armor])
		{
			printf("%s", gPlayer->EquipItem[EEquip::Armor]->Name);

			if (gPlayer->EquipItem[EEquip::Armor]->Upgrade > 0)
				printf(" +%d", gPlayer->EquipItem[EEquip::Armor]->Upgrade);

			printf("\n");
		}

		else
			printf("없음\n");

		printf("보유 골드 : %d\n", gPlayer->Gold);

		printf("메뉴를 선택하세요 : ");
		int Input = 0;
		scanf_s("%d", &Input);

		if (Input <= EInventoryItemMenu::None || Input >= EInventoryItemMenu::End)
		{
			printf("잘못된 값을 입력하였습니다. 다시 입력해주세요.\n");
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

		printf("0. 뒤로 가기\n");

		printf("아이템을 선택하세요 : ");
		int Input = 0;
		scanf_s("%d", &Input);

		if (Input == 0)
		{
			printf("게임을 종료합니다.");
			break;
		}

		else if (Input < 0 || Input > INVENTORY_MAX)
		{
			printf("잘못된 값을 입력하였습니다. 다시 입력해주세요.\n");
			system("pause");
			continue;
		}

		RunItem(Input - 1);
	}
}
