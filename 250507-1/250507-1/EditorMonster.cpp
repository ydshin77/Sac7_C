
#include <iostream>
#include "GameInfo.h"
#include "Battle.h"

// 몬스터 기본 정보 설정

// EditorMonster 메뉴
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

// 파일 쓰기 함수
void Save(FMonsterEditorInfo* Info)
{
	FILE* FileStream = nullptr;

	fopen_s(&FileStream, "MonsterInfo.mst", "wb");

	if (!FileStream)
		return;

	fwrite(Info, sizeof(FMonsterEditorInfo), EMapMenu::MapCount, FileStream);

	fclose(FileStream);
}

// 파일 읽기 함수
void Load(FMonsterEditorInfo* Info)
{
	FILE* FileStream = nullptr;

	fopen_s(&FileStream, "MonsterInfo.mst", "rb");

	if (!FileStream)
		return;

	fread(Info, sizeof(FMonsterEditorInfo), EMapMenu::MapCount, FileStream);

	fclose(FileStream);
}

// 몬스터 정보 수정 함수
void Modify(FMonsterEditorInfo* Info)
{
	// 난이도 선택
	printf("1. 쉬움\n");
	printf("2. 보통\n");
	printf("3. 어려움\n");

	printf("수정할 난이도를 선택하세요 : ");
	int Input = 0;
	scanf_s("%d", &Input);

	if (Input <= EMapMenu::None || Input >= EMapMenu::Back)
		return;

	// 몬스터 정보 수정
	int Index = Input - 1;
	
	printf("이름 : ");
	scanf_s("%s", &Info[Index].Name, 31);

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

	// 입력한 내용을 파일에 저장
	Save(Info);
}

int main()
{
	// 3개 생성 (쉬움, 보통, 어려움)
	FMonsterEditorInfo MonsterInfo[EMapMenu::MapCount] = {};

	while (true)
	{
		system("cls");

		printf("1. 몬스터 수정\n");
		printf("2. 몬스터 삭제\n");
		printf("3. 불러오기\n");
		printf("4. 출력\n");
		printf("5. 종료\n");

		printf("메뉴를 선택하세요 : ");
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
				printf("이름 : %s\n", MonsterInfo[i].Name);
				printf("공격력 : %d\n", MonsterInfo[i].Attack);
				printf("방어력 : %d\n", MonsterInfo[i].Defense);
				printf("체력 : %d\n", MonsterInfo[i].HP);
				printf("마나 : %d\n", MonsterInfo[i].MP);
				printf("레벨 : %d\n", MonsterInfo[i].Level);
				printf("경험치 : %d\n", MonsterInfo[i].Exp);
				printf("골드 : %d\n", MonsterInfo[i].Gold);
				printf("==============\n");
			}
			system("pause");
			break;
		case EEditorMonsterMenu::Exit:
			// 게임이 종료될 때 자동 세이브
			Save(MonsterInfo);
			return 0;
		}

	}

	return 0;
}