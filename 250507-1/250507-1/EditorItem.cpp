
#include <iostream>
#include "GameInfo.h"

// ���� ������ �⺻ ���� ����
// ������ ������ ���� ����, �������� �Ĵ� ������ ��� ����. �̷��� �� �� ����
// ���⼭�� ���� ��Ͽ� ������ �������� �־ �ǽ���

// EditorItem �޴�
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

// ���� ���� �Լ�
void Save(FPlayerEditorInfo* Info)
{
	FILE* FileStream = nullptr;

	fopen_s(&FileStream, "PlayerInfo.pli", "wb");

	if (!FileStream)
		return;

	fwrite(Info, sizeof(FPlayerEditorInfo), 3, FileStream);

	fclose(FileStream);
}

// ���� �б� �Լ�
void Load(FPlayerEditorInfo* Info)
{
	FILE* FileStream = nullptr;

	fopen_s(&FileStream, "PlayerInfo.pli", "rb");

	if (!FileStream)
		return;

	fread(Info, sizeof(FPlayerEditorInfo), 3, FileStream);

	fclose(FileStream);
}

// ������ ���� ���� �Լ�
void Modify(FPlayerEditorInfo* Info)
{
	// ���� ����
	printf("1. ���\n");
	printf("2. �ü�\n");
	printf("3. ������\n");

	printf("������ ������ �����ϼ��� : ");
	int Input = 0;
	scanf_s("%d", &Input);

	if (Input <= 0 || Input >= 4)
		return;

	// �ɷ�ġ ����
	int Index = Input - 1;

	printf("���ݷ� : ");
	scanf_s("%d", &Info[Index].Attack);

	printf("���� : ");
	scanf_s("%d", &Info[Index].Defense);

	printf("ü�� : ");
	scanf_s("%d", &Info[Index].HP);

	printf("���� : ");
	scanf_s("%d", &Info[Index].MP);

	// �Է��� ������ ���Ͽ� ����
	Save(Info);
}

// ������ ���� �Լ�
// ���ڿ� FItem** ItemArray��� �� ���, �迭�� ���� �����Ǿ��� �� �迭�� �ּҰ�
// ������ ���� �����Ϳ��� ����ǰ� ������ ���� �����Ϳ��� ������� ����
// => ���� ������ ���۷����� ����ؾ� ������ ���� �����Ϳ��� ���ο� �迭�� �ּҰ� �����
// Capacity�� Count ���� ����� �� ������ ���۷��� ��� (�ܼ� �� ������ �����̸� �����ͺ��� ���۷��� ���)
void Create(FItem**& ItemArray, int& Capacity, int& Count)
{
	// �迭�� �� á���� Ȯ���ϰ�, �� á�ٸ� �迭 ������ �÷���
	if (Capacity == Count)
	{
		// �迭 ������ 2��� �÷���
		Capacity *= 2;

		// �÷��� ���� ����ŭ �迭�� ���� ����
		FItem** NewArray = new FItem* [Capacity];

		// ���� �迭�� �ִ� ������ ���ο� �迭�� �־���
		for (int i = 0; i < Count; ++i)
		{
			NewArray[i] = ItemArray[i];
		}

		// ���� �迭 ����
		SAFE_DELETE_ARRAY(ItemArray);

		// ���� �迭�� �ּҸ� ���ο� �迭�� �ּҷ� ����
		ItemArray = NewArray;
	}

	system("cls");

	printf("1. ����\n");
	printf("2. ��\n");

	printf("�߰��� ������ ������ �����ϼ��� : ");
	int ItemType = 0;
	scanf_s("%d", &ItemType);

	if (ItemType <= EItemType::None || ItemType >= EItemType::End)
		return;

	// ������ ����
	FItem* Item = new FItem;

	// int�� ������ �ȿ� ���� ���� ����ȯ�� ���־�� ��
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

	printf("���� ���� ���� : ");
	scanf_s("%d", &Item->Price);

	printf("���� �Ǹ� ���� : ");
	scanf_s("%d", &Item->Sell);

	ItemArray[Count] = Item;
	++Count;
}

int main()
{
	// ��ü �迭 ũ��
	int ItemCapacity = 2;

	// �迭�� �߰��� ������ ����
	int ItemCount = 0;

	// ������ ������ �þ ���� ������ ���� �迭�� ����
	// ��� 1. ���� ������ ��� -> �޸� �ּҸ� �����ϴ� �迭 �� �� ����
	FItem** ItemArray = new FItem* [ItemCapacity];

	// ��� 2. ������ ���		-> ������ ������ �����ϴ� �迭 �� �� ����
	//FItem* ItemArray = new FItem[ItemCapacity];

	while (true)
	{
		system("cls");

		printf("1. ������ �߰�\n");
		printf("2. ������ ����\n");
		printf("3. ������ ����\n");
		printf("4. �ҷ�����\n");
		printf("5. ���\n");
		printf("6. ����\n");

		printf("�޴��� �����ϼ��� : ");
		int Input = 0;
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
			Load(JobInfo);
			break;
		case EEditorItemMenu::Output:
			for (int i = 0; i < 3; ++i)
			{
				printf("���ݷ� : %d\n", JobInfo[i].Attack);
				printf("���� : %d\n", JobInfo[i].Defense);
				printf("ü�� : %d\n", JobInfo[i].HP);
				printf("���� : %d\n", JobInfo[i].MP);
				printf("==============\n");
			}
			system("pause");
			break;
		case EEditorItemMenu::Exit:
			// ������ ����� �� �ڵ� ���̺�
			Save(JobInfo);

			// ���� �迭 ����
			SAFE_DELETE_ARRAY(ItemArray);

			return 0;
		}

	}

	return 0;
}