
#include <iostream>
#include "GameInfo.h"

namespace EEditorItemMenu
{
	enum Type
	{
		None,
		Create,
		Delete,
		Modify,
		Load,
		Output,
		Exit,
		End
	};
}

void Save(FItem** Info, int Count)
{
	FILE* File = nullptr;

	fopen_s(&File, "ItemList.itl", "wb");

	if (!File)
		return;

	// 아이템 몇개를 저장하는지 먼저 저장해둔다.
	fwrite(&Count, sizeof(int), 1, File);

	for (int i = 0; i < Count; ++i)
	{
		// 아이템을 하나하나 저장한다.
		fwrite(Info[i], sizeof(FItem), 1, File);
	}

	fclose(File);
}

void Load(FItem**& Info, int& Capacity, int& Count)
{
	FILE* File = nullptr;

	fopen_s(&File, "ItemList.itl", "rb");

	if (!File)
		return;

	// 기존 배열을 제거한다.
	for (int i = 0; i < Count; ++i)
	{
		SAFE_DELETE(Info[i]);
	}

	SAFE_DELETE_ARRAY(Info);

	fread(&Count, sizeof(int), 1, File);

	Capacity = Count;

	Info = new FItem * [Capacity];

	for (int i = 0; i < Capacity; ++i)
	{
		Info[i] = new FItem;
		fread(Info[i], sizeof(FItem), 1, File);
	}

	fclose(File);
}

void Modify(FItem** Info, int Count)
{
	/*printf("1. 기사\n");
	printf("2. 궁수\n");
	printf("3. 마법사\n");
	printf("수정할 직업을 선택하세요 : ");
	int		Input;
	scanf_s("%d", &Input);

	if (Input <= 0 || Input >= 4)
		return;

	int	Index = Input - 1;

	printf("공격력 : ");
	scanf_s("%d", &Info[Index].Attack);

	printf("방어력 : ");
	scanf_s("%d", &Info[Index].Defense);

	printf("체력 : ");
	scanf_s("%d", &Info[Index].HP);

	printf("마나 : ");
	scanf_s("%d", &Info[Index].MP);*/

	Save(Info, Count);
}

void Create(FItem**& ItemArray, int& Capacity, int& Count)
{
	// 배열이 꽉 찼는지 확인하고 배열이 꽉 찼다면 배열 공간을
	// 늘려준다.
	if (Capacity == Count)
	{
		// 배열 공간을 2배로 늘려준다.
		Capacity *= 2;

		// 늘려준 공간 수만큼 배열을 새롭게 생성한다.
		FItem** NewArray = new FItem * [Capacity];

		// 기존 배열에 있는 정보를 새로운 배열에 넣어준다.
		for (int i = 0; i < Count; ++i)
		{
			NewArray[i] = ItemArray[i];
		}

		// 기존 배열을 제거한다.
		SAFE_DELETE_ARRAY(ItemArray);

		// 기존 배열의 주소를 새로운 배열의 주소로 갱신한다.
		ItemArray = NewArray;
	}

	system("cls");
	printf("1. 무기\n");
	printf("2. 방어구\n");
	printf("추가할 아이템 종류를 선택하세요 : ");
	int	ItemType = 0;
	scanf_s("%d", &ItemType);

	--ItemType;

	if (ItemType <= EItemType::None ||
		ItemType >= EItemType::End)
		return;

	// 아이템을 생성한다.
	FItem* Item = new FItem;

	Item->ItemType = (EItemType::Type)ItemType;

	printf("이름 : ");
	scanf_s("%s", Item->Name, 31);

	switch (Item->ItemType)
	{
	case EItemType::Weapon:
		printf("공격력 : ");
		break;
	case EItemType::Armor:
		printf("방어력 : ");
		break;
	}

	scanf_s("%d", &Item->Option);

	printf("상점구매가격 : ");
	scanf_s("%d", &Item->Price);

	printf("상점판매가격 : ");
	scanf_s("%d", &Item->Sell);

	ItemArray[Count] = Item;
	++Count;

	Save(ItemArray, Count);
}

int main()
{
	/*
	레퍼런스 : 다른 변수를 참조하여 값을 가져와서 사용하거나 값을 변경할 수
	있게 해주는 기능이다.
	레퍼런스는 레퍼런스 변수를 선언하는 동시에 반드시 참조하는 대상을 지정해야
	한다.

	변수타입& 변수명 = 참조할대상변수; 의 방식으로 사용한다.
	*/

	//FPlayerEditorInfo	JobInfo[3] = {};
	//FItem* ItemArray = new FItem[3];

	// 전체 배열의 크기이다.
	int	ItemCapacity = 2;

	// 배열에 추가된 아이템 개수이다.
	int	ItemCount = 0;

	FItem** ItemArray = new FItem * [ItemCapacity];


	while (true)
	{
		system("cls");
		printf("1. 아이템추가\n");
		printf("2. 아이템삭제\n");
		printf("3. 아이템수정\n");
		printf("4. 불러오기\n");
		printf("5. 출력\n");
		printf("6. 종료\n");
		printf("메뉴를 선택하세요 : ");
		int	Input = 0;
		scanf_s("%d", &Input);

		switch (Input)
		{
		case EEditorItemMenu::Create:
			Create(ItemArray, ItemCapacity, ItemCount);
			break;
		case EEditorItemMenu::Delete:
			break;
		case EEditorItemMenu::Modify:
			break;
		case EEditorItemMenu::Load:
			Load(ItemArray, ItemCapacity, ItemCount);
			break;
		case EEditorItemMenu::Output:
			for (int i = 0; i < ItemCount; ++i)
			{
				printf("이름 : %s\n", ItemArray[i]->Name);

				switch (ItemArray[i]->ItemType)
				{
				case EItemType::Weapon:
					printf("종류 : 무기\n");
					printf("공격력 : %d\n", ItemArray[i]->Option);
					break;
				case EItemType::Armor:
					printf("종류 : 방어구\n");
					printf("방어력 : %d\n", ItemArray[i]->Option);
					break;
				}

				printf("상점구매가격 : %d\n", ItemArray[i]->Price);
				printf("상점판매가격 : %d\n", ItemArray[i]->Sell);
			}

			system("pause");
			break;
		case EEditorItemMenu::Exit:
			Save(ItemArray, ItemCount);

			for (int i = 0; i < ItemCount; ++i)
			{
				SAFE_DELETE(ItemArray[i]);
			}

			// 동적배열을 지워준다.
			SAFE_DELETE_ARRAY(ItemArray);

			return 0;
		}
	}

	return 0;
}