
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

	// �������� �� �� ����ƴ��� �ҷ���
	fread(&gItemListCount, sizeof(int), 1, FileStream);

	// ������ ����Ʈ ���� �迭 ����
	gItemList =  new FItem[gItemListCount];

	for (int i = 0; i < gItemListCount; ++i)
	{
		fread(&gItemList[i], sizeof(FItem), 1, FileStream);

		// �о�� �������� �������� �������� ���� ���� �߰�
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

		// ��ü ������ ����ŭ �ݺ��Ͽ� ���⸦ ã�� ���� ������ ����
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

		// ��ü ������ ����ŭ �ݺ��Ͽ� ���� ã�� �� ������ ����
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

// ���� �޴� ���
void OutputStore(EStoreType::Type StoreType)
{
	switch (StoreType)
	{
	case EStoreType::Weapon:
		printf("============== ���� ���� ==============\n");

		for (int i = 0; i < gWeaponStoreCount; ++i)
		{
			printf("%d. %s\n", i + 1, gWeaponStore[i].Name);
		}

		printf("%d. �ڷ� ����\n", gWeaponStoreCount + 1);
		break;
	case EStoreType::Armor:
		printf("============== �� ���� ==============\n");

		for (int i = 0; i < gArmorStoreCount; ++i)
		{
			printf("%d. %s\n", i + 1, gArmorStore[i].Name);
		}

		printf("%d. �ڷ� ����\n", gArmorStoreCount + 1);
		break;
	}

}

// ������ Ÿ�Կ� �´� ���� ���
void RunStore(EStoreType::Type StoreType)
{
	// �̸� ������ ��ϰ� ������ ������ �޾ƿ�
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

		printf("���� ��� : %d\n", gPlayer->Gold);

		printf("������ �������� �����ϼ��� : ");
		int Input = 0;
		scanf_s("%d", &Input);

		if (Input <= 0 || Input > StoreItemCount + 1)
		{
			printf("�߸��� ���� �Է��Ͽ����ϴ�. �ٽ� �Է����ּ���.");
			system("pause");
			continue;
		}
		else if (Input == StoreItemCount + 1)
			return;

		// ������ ������ ��ȣ�� ������ �ε����� ����
		int StoreIndex = Input - 1;

		// �÷��̾ ������ �ݾ��� �������� üũ
		if (gPlayer->Gold < StoreItemList[StoreIndex].Price)
		{
			printf("���� �ݾ��� �����մϴ�.\n");
			system("pause");
			continue;
		}

		// �κ��丮�� ������ �ִ��� üũ
		else if (gInventory->Count == INVENTORY_MAX)
		{
			printf("�κ��丮 ������ �����մϴ�.\n");
			system("pause");
			continue;
		}

		// ������ ����
		FItem* NewItem = new FItem;

		// ������ ����ü�̱� ������ �ϳ��� ������ �����Ͽ� ���� ���� ������ ��
		// �������� ���� ���� ���� (�ּҸ� �����ϴ°� �ƴ϶�)
		*NewItem = StoreItemList[StoreIndex];

		// ���� �ݾ� ����
		gPlayer->Gold -= NewItem->Price;

		// �κ��丮�� �߰�
		// ���� �κ��丮���� ���� �տ� �ִ� �� ���� ã��
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

		printf("1. ���� ����\n");
		printf("2. �� ����\n");
		printf("3. �ڷ� ����\n");
		
		printf("�޴��� �����ϼ��� : ");
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
