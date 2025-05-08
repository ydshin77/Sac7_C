
#include "Store.h"

namespace EStoreType
{
	enum Type
	{
		None,
		Weapon,
		Armor,
		Back,
		End
	};
}

FItem* gWeaponStore = nullptr;
int		gWeaponStoreCount = 0;
FItem* gArmorStore = nullptr;
int		gArmorStoreCount = 0;
FItem* gItemList = nullptr;
int		gItemListCount = 0;

bool StoreInit()
{
	FILE* File = nullptr;

	fopen_s(&File, "ItemList.itl", "rb");

	if (!File)
		return false;

	fread(&gItemListCount, sizeof(int), 1, File);

	gItemList = new FItem[gItemListCount];

	for (int i = 0; i < gItemListCount; ++i)
	{
		fread(&gItemList[i], sizeof(FItem), 1, File);

		// 읽어온 아이템이 무기인지 방어구인지에 따라 개수를 추가해놓는다.
		if (gItemList[i].ItemType == EItemType::Weapon)
			++gWeaponStoreCount;

		else if (gItemList[i].ItemType == EItemType::Armor)
			++gArmorStoreCount;
	}

	fclose(File);

	if (gWeaponStoreCount > 0)
	{
		gWeaponStore = new FItem[gWeaponStoreCount];

		int	Index = 0;

		// 전체 아이템 수만큼 반복하며 무기를 찾아서 무기상점에 넣어준다.
		for (int i = 0; i < gItemListCount; ++i)
		{
			if (gItemList[i].ItemType == EItemType::Weapon)
			{
				gWeaponStore[Index] = gItemList[i];
				++Index;
			}
		}
	}

	if (gArmorStoreCount > 0)
	{
		gArmorStore = new FItem[gArmorStoreCount];

		int	Index = 0;

		// 전체 아이템 수만큼 반복하며 무기를 찾아서 무기상점에 넣어준다.
		for (int i = 0; i < gItemListCount; ++i)
		{
			if (gItemList[i].ItemType == EItemType::Armor)
			{
				gArmorStore[Index] = gItemList[i];
				++Index;
			}
		}
	}


	return true;
}

void StoreDestroy()
{
	SAFE_DELETE_ARRAY(gItemList);
	SAFE_DELETE_ARRAY(gWeaponStore);
	SAFE_DELETE_ARRAY(gArmorStore);
}

void OutputStore(EStoreType::Type StoreType)
{
	switch (StoreType)
	{
	case EStoreType::Weapon:
		printf("============== 무기상점 ==============\n");
		for (int i = 0; i < gWeaponStoreCount; ++i)
		{
			printf("%d. %s\n", i + 1, gWeaponStore[i].Name);
		}

		printf("%d. 뒤로가기\n", gWeaponStoreCount + 1);
		break;
	case EStoreType::Armor:
		printf("============== 방어구상점 ==============\n");
		for (int i = 0; i < gArmorStoreCount; ++i)
		{
			printf("%d. %s\n", i + 1, gArmorStore[i].Name);
		}

		printf("%d. 뒤로가기\n", gArmorStoreCount + 1);
		break;
	}
}

void RunStore(EStoreType::Type StoreType)
{
	FItem* StoreItemList = nullptr;
	int		StoreItemCount = 0;

	switch (StoreType)
	{
	case EStoreType::Weapon:
		StoreItemList = gWeaponStore;
		StoreItemCount = gWeaponStoreCount;
		break;
	case EStoreType::Armor:
		StoreItemList = gArmorStore;
		StoreItemCount = gArmorStoreCount;
		break;
	}

	while (true)
	{
		system("cls");

		OutputStore(StoreType);

		printf("보유골드 : %d\n", gPlayer->Gold);
		printf("구매할 아이템을 선택하세요 : ");
		int	Input = 0;
		scanf_s("%d", &Input);

		if (Input <= 0 || Input > StoreItemCount + 1)
			continue;

		else if (Input == StoreItemCount + 1)
			return;

		// 선택한 아이템 번호를 상점의 인덱스로 변경한다.
		int	StoreIndex = Input - 1;

		// 플레이어가 보유한 금액이 부족한지 체크한다.
		if (gPlayer->Gold < StoreItemList[StoreIndex].Price)
		{
			printf("보유금액이 부족합니다.\n");
			system("pause");
			continue;
		}

		// 인벤토리에 공간이 있는지 체크한다.
		else if (gInventory->Count == INVENTORY_MAX)
		{
			printf("인벤토리 공간이 부족합니다.\n");
			system("pause");
			continue;
		}

		// 아이템을 생성한다.
		FItem* NewItem = new FItem;

		*NewItem = StoreItemList[StoreIndex];

		// 보유금액을 차감한다.
		gPlayer->Gold -= NewItem->Price;

		// 인벤토리에 추가한다.
		// 현재 인벤토리에서 가장 앞에 있는 빈공간을 찾는다.
		for (int i = 0; i < INVENTORY_MAX; ++i)
		{
			if (!gInventory->ItemList[i])
			{
				gInventory->ItemList[i] = NewItem;
				++gInventory->Count;
				break;
			}
		}

	}
}

void RunStore()
{
	while (true)
	{
		system("cls");
		printf("1. 무기상점\n");
		printf("2. 방어구상점\n");
		printf("3. 뒤로가기\n");
		printf("상점을 선택하세요 : ");
		int	Input = 0;
		scanf_s("%d", &Input);

		if (Input <= EStoreType::None || Input >= EStoreType::End)
			continue;

		switch (Input)
		{
		case EStoreType::Weapon:
			RunStore(EStoreType::Weapon);
			break;
		case EStoreType::Armor:
			RunStore(EStoreType::Armor);
			break;
		case EStoreType::Back:
			return;
		}
	}
}
