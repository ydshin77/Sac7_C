
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
	printf("1. 쉬움\n");
	printf("2. 보통\n");
	printf("3. 어려움\n");
	printf("수정할 난이도를 선택하세요 : ");
	int		Input;
	scanf_s("%d", &Input);

	if (Input <= EMapMenu::None || Input >= EMapMenu::Back)
		return;

	int	Index = Input - 1;

	printf("이름 : ");
	scanf_s("%s", Info[Index].Name, 31);

	printf("공격력 : ");
	scanf_s("%d", &Info[Index].Attack);

	printf("방어력 : ");
	scanf_s("%d", &Info[Index].Defense);

	printf("체력 : ");
	scanf_s("%d", &Info[Index].HP);

	printf("마나 : ");
	scanf_s("%d", &Info[Index].MP);

	printf("레벨 : ");
	scanf_s("%d", &Info[Index].Level);

	printf("경험치 : ");
	scanf_s("%d", &Info[Index].Exp);

	printf("골드 : ");
	scanf_s("%d", &Info[Index].Gold);

	Save(Info);
}

int main()
{
	FMonsterEditorInfo	MonsterInfo[EMapMenu::MapCount] = {};


	while (true)
	{
		system("cls");
		printf("1. 몬스터수정\n");
		printf("2. 몬스터삭제\n");
		printf("3. 불러오기\n");
		printf("4. 출력\n");
		printf("5. 종료\n");
		printf("메뉴를 선택하세요 : ");
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
				printf("이름 : %s\n", MonsterInfo[i].Name);
				printf("공격력 : %d\n", MonsterInfo[i].Attack);
				printf("방어력 : %d\n", MonsterInfo[i].Defense);
				printf("체력 : %d\n", MonsterInfo[i].HP);
				printf("마나 : %d\n", MonsterInfo[i].MP);
				printf("레벨 : %d\n", MonsterInfo[i].Level);
				printf("경험치 : %d\n", MonsterInfo[i].Exp);
				printf("골드 : %d\n", MonsterInfo[i].Gold);
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