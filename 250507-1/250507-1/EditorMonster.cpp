
#include <iostream>
#include "GameInfo.h"
#include "Battle.h"

// ���� �⺻ ���� ����

// EditorMonster �޴�
namespace EEditorMonsterMenu
{
	enum Type
	{
		None,
		Modify,
		Delete,
		Load,
		Output,
		Exit,
		End
	};
}

// ���� ���� �Լ�
void Save(FMonsterEditorInfo* Info)
{
	FILE* FileStream = nullptr;

	fopen_s(&FileStream, "MonsterInfo.mst", "wb");

	if (!FileStream)
		return;

	fwrite(Info, sizeof(FMonsterEditorInfo), EMapMenu::MapCount, FileStream);

	fclose(FileStream);
}

// ���� �б� �Լ�
void Load(FMonsterEditorInfo* Info)
{
	FILE* FileStream = nullptr;

	fopen_s(&FileStream, "MonsterInfo.mst", "rb");

	if (!FileStream)
		return;

	fread(Info, sizeof(FMonsterEditorInfo), EMapMenu::MapCount, FileStream);

	fclose(FileStream);
}

// ���� ���� ���� �Լ�
void Modify(FMonsterEditorInfo* Info)
{
	// ���̵� ����
	printf("1. ����\n");
	printf("2. ����\n");
	printf("3. �����\n");

	printf("������ ���̵��� �����ϼ��� : ");
	int Input = 0;
	scanf_s("%d", &Input);

	if (Input <= EMapMenu::None || Input >= EMapMenu::Back)
		return;

	// ���� ���� ����
	int Index = Input - 1;
	
	printf("�̸� : ");
	scanf_s("%s", &Info[Index].Name, 31);

	printf("���ݷ� : ");
	scanf_s("%d", &Info[Index].Attack);

	printf("���� : ");
	scanf_s("%d", &Info[Index].Defense);

	printf("ü�� : ");
	scanf_s("%d", &Info[Index].HP);

	printf("���� : ");
	scanf_s("%d", &Info[Index].MP);

	printf("���� : ");
	scanf_s("%d", &Info[Index].Level);

	printf("����ġ : ");
	scanf_s("%d", &Info[Index].Exp);

	printf("��� : ");
	scanf_s("%d", &Info[Index].Gold);

	// �Է��� ������ ���Ͽ� ����
	Save(Info);
}

int main()
{
	// 3�� ���� (����, ����, �����)
	FMonsterEditorInfo MonsterInfo[EMapMenu::MapCount] = {};

	while (true)
	{
		system("cls");

		printf("1. ���� ����\n");
		printf("2. ���� ����\n");
		printf("3. �ҷ�����\n");
		printf("4. ���\n");
		printf("5. ����\n");

		printf("�޴��� �����ϼ��� : ");
		int Input = 0;
		scanf_s("%d", &Input);

		switch (Input)
		{
		case EEditorMonsterMenu::Modify:
			Modify(MonsterInfo);
			break;
		case EEditorMonsterMenu::Delete:
			break;
		case EEditorMonsterMenu::Load:
			Load(MonsterInfo);
			break;
		case EEditorMonsterMenu::Output:
			for (int i = 0; i < EMapMenu::MapCount; ++i)
			{
				printf("�̸� : %s\n", MonsterInfo[i].Name);
				printf("���ݷ� : %d\n", MonsterInfo[i].Attack);
				printf("���� : %d\n", MonsterInfo[i].Defense);
				printf("ü�� : %d\n", MonsterInfo[i].HP);
				printf("���� : %d\n", MonsterInfo[i].MP);
				printf("���� : %d\n", MonsterInfo[i].Level);
				printf("����ġ : %d\n", MonsterInfo[i].Exp);
				printf("��� : %d\n", MonsterInfo[i].Gold);
				printf("==============\n");
			}
			system("pause");
			break;
		case EEditorMonsterMenu::Exit:
			// ������ ����� �� �ڵ� ���̺�
			Save(MonsterInfo);
			return 0;
		}

	}

	return 0;
}