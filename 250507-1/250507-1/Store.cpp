
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
int gWeaponStoreCount = 0;
FItem* gArmorStore = nullptr;
int gArmorStoreCount = 0;
FItem* gItemList = nullptr;
int gItemListCount = 0;

bool StoreInit()
{
	FILE* FileStream = nullptr;

	fopen_s(&FileStream, "ItemList.itl", "rb");

	if (!FileStream)
		return false;

	// 아이템이 몇 개 저장됐는지 불러옴
	fread(&gItemListCount, sizeof(int), 1, FileStream);

	// 아이템 리스트 동적 배열 생성
	gItemList =  new FItem[gItemListCount];

	for (int i = 0; i < gItemListCount; ++i)
	{
		fread(&gItemList[i], sizeof(FItem), 1, FileStream);

		// 읽어온 아이템이 무기인지 방어구인지에 따라 개수 추가
		if (gItemList[i].ItemType == EItemType::Weapon)
			++gWeaponStoreCount;

		else if (gItemList[i].ItemType == EItemType::Armor)
			++gArmorStoreCount;
	}

	fclose(FileStream);

	if (gWeaponStoreCount > 0)
	{
		gWeaponStore = new FItem[gWeaponStoreCount];

		int Index = 0;

		// 전체 아이템 수만큼 반복하여 무기를 찾고 무기 상점에 넣음
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

		int Index = 0;

		// 전체 아이템 수만큼 반복하여 방어구를 찾고 방어구 상점에 넣음
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

// 상점 메뉴 출력
void OutputStore(EStoreType::Type StoreType)
{
	switch (StoreType)
	{
	case EStoreType::Weapon:
		printf("============== 무기 상점 ==============\n");

		for (int i = 0; i < gWeaponStoreCount; ++i)
		{
			printf("%d. %s\n", i + 1, gWeaponStore[i].Name);
		}

		printf("%d. 뒤로 가기\n", gWeaponStoreCount + 1);
		break;
	case EStoreType::Armor:
		printf("============== 방어구 상점 ==============\n");

		for (int i = 0; i < gArmorStoreCount; ++i)
		{
			printf("%d. %s\n", i + 1, gArmorStore[i].Name);
		}

		printf("%d. 뒤로 가기\n", gArmorStoreCount + 1);
		break;
	}

}

// 선택한 타입에 맞는 상점 출력
void RunStore(EStoreType::Type StoreType)
{
	// 미리 아이템 목록과 아이템 개수를 받아옴
	FItem* StoreItemList = nullptr;
	int StoreItemCount = 0;

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

		printf("보유 골드 : %d\n", gPlayer->Gold);

		printf("구매할 아이템을 선택하세요 : ");
		int Input = 0;
		scanf_s("%d", &Input);

		if (Input <= 0 || Input > StoreItemCount + 1)
		{
			printf("잘못된 값을 입력하였습니다. 다시 입력해주세요.");
			system("pause");
			continue;
		}
		else if (Input == StoreItemCount + 1)
			return;

		// 선택한 아이템 번호를 상점의 인덱스로 변경
		int StoreIndex = Input - 1;

		// 플레이어가 보유한 금액이 부족한지 체크
		if (gPlayer->Gold < StoreItemList[StoreIndex].Price)
		{
			printf("보유 금액이 부족합니다.\n");
			system("pause");
			continue;
		}

		// 인벤토리에 공간이 있는지 체크
		else if (gInventory->Count == INVENTORY_MAX)
		{
			printf("인벤토리 공간이 부족합니다.\n");
			system("pause");
			continue;
		}

		// 아이템 생성
		FItem* NewItem = new FItem;

		// 동일한 구조체이기 때문에 하나를 통으로 대입하여 같은 값을 가지게 함
		// 역참조를 통해 값을 넣음 (주소를 대입하는게 아니라서)
		*NewItem = StoreItemList[StoreIndex];

		// 보유 금액 차감
		gPlayer->Gold -= NewItem->Price;

		// 인벤토리에 추가
		// 현재 인벤토리에서 가장 앞에 있는 빈 공간 찾기
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

		printf("1. 무기 상점\n");
		printf("2. 방어구 상점\n");
		printf("3. 뒤로 가기\n");
		
		printf("메뉴를 선택하세요 : ");
		int Input = 0;
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
