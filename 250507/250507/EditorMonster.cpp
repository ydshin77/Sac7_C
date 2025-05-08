
#include <iostream>
#include "GameInfo.h"
#include "Battle.h"

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

void Save(FMonsterEditorInfo* Info)
{
	FILE* File = nullptr;

	fopen_s(&File, "MonsterInfo.mst", "wb");

	if (!File)
		return;

	fwrite(Info, sizeof(FMonsterEditorInfo),
		EMapMenu::MapCount, File);

	fclose(File);
}

void Load(FMonsterEditorInfo* Info)
{
	FILE* File = nullptr;

	fopen_s(&File, "MonsterInfo.mst", "rb");

	if (!File)
		return;

	fread(Info, sizeof(FMonsterEditorInfo),
		EMapMenu::MapCount, File);

	fclose(File);
}

void Modify(FMonsterEditorInfo* Info)
{
	printf("1. ����\n");
	printf("2. ����\n");
	printf("3. �����\n");
	printf("������ ���̵��� �����ϼ��� : ");
	int		Input;
	scanf_s("%d", &Input);

	if (Input <= EMapMenu::None || Input >= EMapMenu::Back)
		return;

	int	Index = Input - 1;

	printf("�̸� : ");
	scanf_s("%s", Info[Index].Name, 31);

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

	Save(Info);
}

int main()
{
	FMonsterEditorInfo	MonsterInfo[EMapMenu::MapCount] = {};


	while (true)
	{
		system("cls");
		printf("1. ���ͼ���\n");
		printf("2. ���ͻ���\n");
		printf("3. �ҷ�����\n");
		printf("4. ���\n");
		printf("5. ����\n");
		printf("�޴��� �����ϼ��� : ");
		int	Input = 0;
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
			}

			system("pause");
			break;
		case EEditorMonsterMenu::Exit:
			Save(MonsterInfo);
			return 0;
		}
	}

	return 0;
}