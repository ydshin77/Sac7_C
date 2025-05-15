
#include "Battle.h"

// 전투 메뉴
namespace EBattleMenu
{
	enum Type
	{
		None,
		Attack,
		Back,
		End
	};
}

// 전투 결과
enum class EBattleResult : unsigned char
{
	None,
	PlayerDeath,
	MonsterDeath
};

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
	printf("이름 : %s\t\t직업 : ", gPlayer->Name);

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

	printf("레벨 : %d\t\t경험치 : %d\n", gPlayer->Level, gPlayer->Exp);
	printf("공격력 : %d\t\t방어력 : %d\n", gPlayer->Attack, gPlayer->Defense);
	printf("체력 : %d / %d\t마나 : %d / %d\n", 
		gPlayer->HP, gPlayer->HPMax, gPlayer->MP, gPlayer->MPMax);
	printf("골드 : %d\n", gPlayer->Gold);
}

// 몬스터 정보 출력
void OutputMonsterBattle(FMonsterInfo* Monster)
{
	printf("이름 : %s\t\t레벨 : %d\n", Monster->Name, Monster->Level);
	printf("공격력 : %d\t\t방어력 : %d\n", Monster->Attack, Monster->Defense);
	printf("체력 : %d / %d\t마나 : %d / %d\n",
		Monster->HP, Monster->HPMax, Monster->MP, Monster->MPMax);
	printf("획득 경험치 : %d\t획득 골드 : %d\n", Monster->Exp, Monster->Gold);
}

// 전투 함수
EBattleResult Battle(FMonsterInfo* Monster)
{
	// 플레이어가 몬스터를 공격
	int Damage = gPlayer->Attack - Monster->Defense;

	// 데미지가 최소 1이라도 들어갈 수 있도록 함
	// 방법 1. 삼항연산자 사용
	Damage = Damage <= 0 ? 1 : Damage;

	printf("Player가 Monster에게 %d 데미지를 주었습니다.\n", Damage);

	// 방법 2. if문 사용
	/*if (Damage <= 0)
		Damage = 1;*/

	// 몬스터 체력 감소
	Monster->HP -= Damage;

	// 몬스터가 죽었는지 확인
	if (Monster->HP <= 0)
	{
		// 경험치와 골드 습득
		gPlayer->Exp += Monster->Exp;
		gPlayer->Gold += Monster->Gold;

		printf("Monster가 죽었습니다.\n");

		system("pause");

		return EBattleResult::MonsterDeath;
	}

	// 몬스터가 플레이어를 공격
	Damage = Monster->Attack - gPlayer->Defense;

	Damage = Damage <= 0 ? 1 : Damage;

	printf("Monster가 Player에게 %d 데미지를 주었습니다.\n", Damage);

	// 플레이어 체력 감소
	gPlayer->HP -= Damage;

	// 플레이어가 죽었는지 확인
	if (gPlayer->HP <= 0)
	{
		// 플레이어가 죽었을 경우
		// 경험치와 골드 10% 감소, 체력과 마나를 최대치로 하여 부활시킴
		gPlayer->Exp = (int)(gPlayer->Exp * 0.9f);
		gPlayer->Gold = (int)(gPlayer->Gold * 0.9f);
		gPlayer->HP = gPlayer->HPMax;
		gPlayer->MP = gPlayer->MPMax;

		printf("Player가 죽었습니다.\n");

		system("pause");

		return EBattleResult::PlayerDeath;
	}

	system("pause");

	return EBattleResult::None;
}

// 몬스터 생성 함수
FMonsterInfo* CreateMonster(EMapMenu::Type BattleType)
{
	// 난이도에 맞는 몬스터 생성
	FMonsterInfo* Monster = new FMonsterInfo;

	int MenuIndex = BattleType - 1;

	strcpy_s(Monster->Name, gMonsterOriginInfo[MenuIndex].Name);
	Monster->Attack = gMonsterOriginInfo[MenuIndex].Attack;
	Monster->Defense = gMonsterOriginInfo[MenuIndex].Defense;
	Monster->HP = gMonsterOriginInfo[MenuIndex].HP;
	Monster->HPMax = gMonsterOriginInfo[MenuIndex].HP;
	Monster->MP = gMonsterOriginInfo[MenuIndex].MP;
	Monster->MPMax = gMonsterOriginInfo[MenuIndex].MP;
	Monster->Level = gMonsterOriginInfo[MenuIndex].Level;
	Monster->Exp = gMonsterOriginInfo[MenuIndex].Exp;
	Monster->Gold = gMonsterOriginInfo[MenuIndex].Gold;

	return Monster;
}

// 전투 실행 함수
void RunBattle(EMapMenu::Type BattleType)
{
	// 몬스터 생성
	FMonsterInfo* Monster = CreateMonster(BattleType);

	// 전투 실행
	while (true)
	{
		system("cls");

		// 플레이어, 몬스터 정보 출력
		printf("================= Player =================\n");
		OutputPlayerBattle();

		printf("================= Monster =================\n");
		OutputMonsterBattle(Monster);

		// 전투 메뉴
		printf("1. 공격\n");
		printf("2. 도망가기\n");

		printf("메뉴를 선택하세요 : ");
		int Input = 0;
		scanf_s("%d", &Input);

		if (Input <= EBattleMenu::None || Input >= EBattleMenu::End)
		{
			printf("잘못된 값을 입력하였습니다. 다시 입력해주세요.");
			continue;
		}

		switch (Input)
		{
		case EBattleMenu::Attack:
			if (Battle(Monster) == EBattleResult::MonsterDeath)
			{
				// 몬스터가 죽었을 경우 새로운 몬스터 소환
				// 방법 1. 죽은 몬스터를 제거하고 다시 생성 (일반적)
				SAFE_DELETE(Monster);

				Monster = CreateMonster(BattleType);

				// 방법 2. 체력, 마나 회복시킴
				/*Monster->HP = Monster->HPMax;
				Monster->MP = Monster->MPMax;*/
			}
			break;
		case EBattleMenu::Back:
			// 메모리 제거가 없을 경우 메모리 릭이 남게 됨
			SAFE_DELETE(Monster);
			return;
		}

	}
}

void RunMap()
{
	while (true)
	{
		system("cls");

		// 배틀 메뉴 출력 및 선택
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
