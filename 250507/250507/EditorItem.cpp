
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

	// ������ ��� �����ϴ��� ���� �����صд�.
	fwrite(&Count, sizeof(int), 1, File);

	for (int i = 0; i < Count; ++i)
	{
		// �������� �ϳ��ϳ� �����Ѵ�.
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

	// ���� �迭�� �����Ѵ�.
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
	/*printf("1. ���\n");
	printf("2. �ü�\n");
	printf("3. ������\n");
	printf("������ ������ �����ϼ��� : ");
	int		Input;
	scanf_s("%d", &Input);

	if (Input <= 0 || Input >= 4)
		return;

	int	Index = Input - 1;

	printf("���ݷ� : ");
	scanf_s("%d", &Info[Index].Attack);

	printf("���� : ");
	scanf_s("%d", &Info[Index].Defense);

	printf("ü�� : ");
	scanf_s("%d", &Info[Index].HP);

	printf("���� : ");
	scanf_s("%d", &Info[Index].MP);*/

	Save(Info, Count);
}

void Create(FItem**& ItemArray, int& Capacity, int& Count)
{
	// �迭�� �� á���� Ȯ���ϰ� �迭�� �� á�ٸ� �迭 ������
	// �÷��ش�.
	if (Capacity == Count)
	{
		// �迭 ������ 2��� �÷��ش�.
		Capacity *= 2;

		// �÷��� ���� ����ŭ �迭�� ���Ӱ� �����Ѵ�.
		FItem** NewArray = new FItem * [Capacity];

		// ���� �迭�� �ִ� ������ ���ο� �迭�� �־��ش�.
		for (int i = 0; i < Count; ++i)
		{
			NewArray[i] = ItemArray[i];
		}

		// ���� �迭�� �����Ѵ�.
		SAFE_DELETE_ARRAY(ItemArray);

		// ���� �迭�� �ּҸ� ���ο� �迭�� �ּҷ� �����Ѵ�.
		ItemArray = NewArray;
	}

	system("cls");
	printf("1. ����\n");
	printf("2. ��\n");
	printf("�߰��� ������ ������ �����ϼ��� : ");
	int	ItemType = 0;
	scanf_s("%d", &ItemType);

	--ItemType;

	if (ItemType <= EItemType::None ||
		ItemType >= EItemType::End)
		return;

	// �������� �����Ѵ�.
	FItem* Item = new FItem;

	Item->ItemType = (EItemType::Type)ItemType;

	printf("�̸� : ");
	scanf_s("%s", Item->Name, 31);

	switch (Item->ItemType)
	{
	case EItemType::Weapon:
		printf("���ݷ� : ");
		break;
	case EItemType::Armor:
		printf("���� : ");
		break;
	}

	scanf_s("%d", &Item->Option);

	printf("�������Ű��� : ");
	scanf_s("%d", &Item->Price);

	printf("�����ǸŰ��� : ");
	scanf_s("%d", &Item->Sell);

	ItemArray[Count] = Item;
	++Count;

	Save(ItemArray, Count);
}

int main()
{
	/*
	���۷��� : �ٸ� ������ �����Ͽ� ���� �����ͼ� ����ϰų� ���� ������ ��
	�ְ� ���ִ� ����̴�.
	���۷����� ���۷��� ������ �����ϴ� ���ÿ� �ݵ�� �����ϴ� ����� �����ؾ�
	�Ѵ�.

	����Ÿ��& ������ = �����Ҵ�󺯼�; �� ������� ����Ѵ�.
	*/

	//FPlayerEditorInfo	JobInfo[3] = {};
	//FItem* ItemArray = new FItem[3];

	// ��ü �迭�� ũ���̴�.
	int	ItemCapacity = 2;

	// �迭�� �߰��� ������ �����̴�.
	int	ItemCount = 0;

	FItem** ItemArray = new FItem * [ItemCapacity];


	while (true)
	{
		system("cls");
		printf("1. �������߰�\n");
		printf("2. �����ۻ���\n");
		printf("3. �����ۼ���\n");
		printf("4. �ҷ�����\n");
		printf("5. ���\n");
		printf("6. ����\n");
		printf("�޴��� �����ϼ��� : ");
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
				printf("�̸� : %s\n", ItemArray[i]->Name);

				switch (ItemArray[i]->ItemType)
				{
				case EItemType::Weapon:
					printf("���� : ����\n");
					printf("���ݷ� : %d\n", ItemArray[i]->Option);
					break;
				case EItemType::Armor:
					printf("���� : ��\n");
					printf("���� : %d\n", ItemArray[i]->Option);
					break;
				}

				printf("�������Ű��� : %d\n", ItemArray[i]->Price);
				printf("�����ǸŰ��� : %d\n", ItemArray[i]->Sell);
			}

			system("pause");
			break;
		case EEditorItemMenu::Exit:
			Save(ItemArray, ItemCount);

			for (int i = 0; i < ItemCount; ++i)
			{
				SAFE_DELETE(ItemArray[i]);
			}

			// �����迭�� �����ش�.
			SAFE_DELETE_ARRAY(ItemArray);

			return 0;
		}
	}

	return 0;
}