
#include "Battle.h"

// 전투 초기화 때, MonsterInfo 파일에서 읽어온 정보를 저장할 전역변수 선언
FMonsterEditorInfo gMonsterOriginInfo[EMapMenu::MapCount];

bool BattleInit()
{
	// MonsterInfo 파일로부터 몬스터 정보를 읽어서 메모리에 저장
	FILE* FileStream = nullptr;

	fopen_s(&FileStream, "MonsterInfo.mst", "rb");

	if (!FileStream)
		return false;

	fread(gMonsterOriginInfo, sizeof(FMonsterEditorInfo), EMapMenu::MapCount, FileStream);

	fclose(FileStream);

	return true;
}

// 플레이어 정보 출력
// gPlayer는 전역변수(extern)로 선언했기 때문에 인자는 따로 필요없음
void OutputPlayerBattle()
{
	printf("이름 : %s\t직업 : ", gPlayer->Name);

	switch (gPlayer->Job)
	{
	case EPlayerJob::Knight:
		printf("기사\n");
		break;
	case EPlayerJob::Archer:
		printf("궁수\n");
		break;
	case EPlayerJob::Magicion:
		printf("마법사\n");
		break;
	}

	printf("레벨 : %d\t경험치 : %d\n", gPlayer->Level, gPlayer->Exp);
	printf("공격력 : %d\t방어력 : %d\n", gPlayer->Attack, gPlayer->Defense);
	printf("체력 : %d / %d\t마나 : %d / %d\n", 
		gPlayer->HP, gPlayer->HPMax, gPlayer->MP, gPlayer->MPMax);
	printf("골드 : %d\n", gPlayer->Gold);
}

// 몬스터 정보 출력
void OutputMonsterBattle(FMonsterInfo* Monster)
{
	printf("이름 : %s\n\t레벨 : %d\n", Monster->Name, Monster->Level);
	printf("획득 경험치 : %d\t획득 골드 : %d\n", Monster->Exp, Monster->Gold);
	printf("공격력 : %d\t방어력 : %d\n", Monster->Attack, Monster->Defense);
	printf("체력 : %d / %d\t마나 : %d / %d\n",
		Monster->HP, Monster->HPMax, Monster->MP, Monster->MPMax);
}

// 전투 실행 함수
void RunBattle(EMapMenu::Type BattleType)
{
	// 난이도에 맞는 몬스터 생성
	FMonsterInfo* Monster = new FMonsterInfo;

	int MenuIndex = BattleType - 1;

	strcpy_s(Monster->Name, gMonsterOriginInfo[MenuIndex].Name);
	Monster->Attack, gMonsterOriginInfo[MenuIndex].Attack;
	Monster->Defense, gMonsterOriginInfo[MenuIndex].Defense;
	Monster->HP, gMonsterOriginInfo[MenuIndex].HP;
	Monster->HPMax, gMonsterOriginInfo[MenuIndex].HP;
	Monster->MP, gMonsterOriginInfo[MenuIndex].MP;
	Monster->MPMax, gMonsterOriginInfo[MenuIndex].MP;
	Monster->Level, gMonsterOriginInfo[MenuIndex].Level;
	Monster->Exp, gMonsterOriginInfo[MenuIndex].Exp;
	Monster->Gold, gMonsterOriginInfo[MenuIndex].Gold;

	// 전투 실행
	while (true)
	{
		system("cls");

		// 플레이어, 몬스터 정보 출력
		printf("================= Player =================\n");
		OutputPlayerBattle();

		printf("================= Monster =================\n");
		OutputMonsterBattle(Monster);
	}
}

void RunMap()
{
	while (true)
	{
		system("cls");

		// 전투 메뉴 출력 및 선택
		printf("1. 쉬움\n");
		printf("2. 보통\n");
		printf("3. 어려움\n");
		printf("4. 뒤로가기\n");

		printf("메뉴를 선택하세요 : ");
		int Input = 0;
		scanf_s("%d", &Input);

		switch (Input)
		{
		case EMapMenu::Easy:
			RunBattle(EMapMenu::Easy);
			break;
		case EMapMenu::Normal:
			RunBattle(EMapMenu::Normal);
			break;
		case EMapMenu::Hard:
			RunBattle(EMapMenu::Hard);
			break;
		case EMapMenu::Back:
			return;
		}

	}
}
