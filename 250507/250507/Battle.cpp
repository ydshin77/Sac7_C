
#include "Battle.h"

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

enum class EBattleResult : unsigned char
{
	None,
	PlayerDeath,
	MonsterDeath
};

FMonsterEditorInfo	gMonsterOriginInfo[EMapMenu::MapCount];

int* gExpTable = nullptr;

bool BattleInit()
{
	// 몬스터 파일로부터 몬스터 정보를 읽어서 메모리에 올려둔다.
	FILE* File = nullptr;

	fopen_s(&File, "MonsterInfo.mst", "rb");

	if (!File)
		return false;

	fread(gMonsterOriginInfo, sizeof(FMonsterEditorInfo),
		EMapMenu::MapCount, File);

	fclose(File);

	// 경험치 테이블을 읽어온다.
	fopen_s(&File, "ExpTable.txt", "rt");

	if (!File)
		return false;

	char	Line[512] = {};

	fgets(Line, 512, File);

	int	TableCount = atoi(Line);

	gExpTable = new int[TableCount];

	fgets(Line, 512, File);

	// 문자열을 분리한다.
	char* Context = nullptr;
	char* TokResult = strtok_s(Line, ",", &Context);

	gExpTable[0] = atoi(TokResult);

	for (int i = 1; i < TableCount; ++i)
	{
		TokResult = strtok_s(nullptr, ",", &Context);

		gExpTable[i] = atoi(TokResult);
	}

	fclose(File);

	return true;
}

void BattleDestroy()
{
	SAFE_DELETE_ARRAY(gExpTable);
}

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

	printf("레벨 : %d\t경험치 : %d / %d\n", gPlayer->Level,
		gPlayer->Exp, gExpTable[gPlayer->Level - 1]);
	/*printf("공격력 : %d\t방어력 : %d\n", gPlayer->Attack,
		gPlayer->Defense);*/

	printf("공격력 : %d", gPlayer->Attack);

	if (gPlayer->EquipItem[EEquip::Weapon])
		printf(" + %d", gPlayer->EquipItem[EEquip::Weapon]->Option);

	printf("\t방어력 : %d", gPlayer->Defense);

	if (gPlayer->EquipItem[EEquip::Armor])
		printf(" + %d", gPlayer->EquipItem[EEquip::Armor]->Option);

	printf("\n");

	printf("체력 : %d / %d\t마나 : %d / %d\n",
		gPlayer->HP, gPlayer->HPMax,
		gPlayer->MP, gPlayer->MPMax);
	printf("골드 : %d\n", gPlayer->Gold);

	printf("장착무기 : ");

	if (gPlayer->EquipItem[EEquip::Weapon])
		printf("%s\t", gPlayer->EquipItem[EEquip::Weapon]->Name);

	else
		printf("없음\t");

	printf("장착방어구 : ");

	if (gPlayer->EquipItem[EEquip::Armor])
		printf("%s\n", gPlayer->EquipItem[EEquip::Armor]->Name);

	else
		printf("없음\n");
}

void OutputMonsterBattle(FMonsterInfo* Monster)
{
	printf("이름 : %s\t레벨 : %d\n", Monster->Name,
		Monster->Level);

	printf("획득경험치 : %d\t획득골드 : %d\n", Monster->Exp,
		Monster->Gold);
	printf("공격력 : %d\t방어력 : %d\n", Monster->Attack,
		Monster->Defense);
	printf("체력 : %d / %d\t마나 : %d / %d\n",
		Monster->HP, Monster->HPMax,
		Monster->MP, Monster->MPMax);
}

EBattleResult Battle(FMonsterInfo* Monster)
{
	// 플레이어가 몬스터를 공격한다.
	// 장착 무기가 있을 경우 추가 공격력이 적용되어야 한다.
	int	Attack = gPlayer->Attack;

	if (gPlayer->EquipItem[EEquip::Weapon])
		Attack += gPlayer->EquipItem[EEquip::Weapon]->Option;

	int	Damage = Attack - Monster->Defense;

	// 최소데미지가 1은 들어갈 수 있게 한다.
	// 삼항연산자 : 왼쪽의 조건식이 true일 경우 : 왼쪽의 값이 반환되고
	// false일 경우 : 오른쪽의 값이 반환된다.
	Damage = Damage <= 0 ? 1 : Damage;
	/*if (Damage <= 0)
		Damage = 1;*/

	printf("Player가 Monster에게 %d 데미지를 주었습니다.\n", Damage);

	Monster->HP -= Damage;

	// 몬스터가 죽었는지 확인한다.
	if (Monster->HP <= 0)
	{
		// 경험치와 골드를 습득하게 한다.
		gPlayer->Exp += Monster->Exp;
		gPlayer->Gold += Monster->Gold;

		printf("Monster가 죽었습니다.\n");

		// 인벤토리에 공간이 있을 경우에만 아이템을 획득할 수 있게 한다.
		if (gInventory->Count < INVENTORY_MAX)
		{
			// 아이템을 드랍할 확률을 구한다.
			float	Percent = rand() % 10000 / 100.f;

			// 20% 확률로 아이템을 획득한다.
			if (Percent < 20.f)
			{
				// 어떤 아이템을 드랍할지 결정한다.
				int	DropIndex = rand() % gItemListCount;

				FItem* DropItem = new FItem;

				*DropItem = gItemList[DropIndex];

				// 인벤토리의 빈 공간을 찾아 아이템을 넣어준다.
				for (int i = 0; i < INVENTORY_MAX; ++i)
				{
					if (!gInventory->ItemList[i])
					{
						gInventory->ItemList[i] = DropItem;
						++gInventory->Count;
						break;
					}
				}

				printf("%s 아이템을 획득하였습니다.\n",
					DropItem->Name);
				system("pause");
			}
		}


		// 레벨업 했는지 확인.
		if (gPlayer->Exp >= gExpTable[gPlayer->Level - 1])
		{
			gPlayer->Exp -= gExpTable[gPlayer->Level - 1];

			++gPlayer->Level;

			gPlayer->Attack = (int)(gPlayer->Attack * 1.1f);
			gPlayer->Defense = (int)(gPlayer->Defense * 1.1f);
			gPlayer->HPMax = (int)(gPlayer->HPMax * 1.1f);
			gPlayer->MPMax = (int)(gPlayer->MPMax * 1.1f);

			gPlayer->HP = gPlayer->HPMax;
			gPlayer->MP = gPlayer->MPMax;

			printf("레벨이 올랐습니다.\n");
		}

		system("pause");

		return EBattleResult::MonsterDeath;
	}

	// 몬스터가 플레이어를 공격한다.
	// 장착방어구가 있을 경우 추가 방어력을 적용한다.
	int	Defense = gPlayer->Defense;

	if (gPlayer->EquipItem[EEquip::Armor])
		Defense += gPlayer->EquipItem[EEquip::Armor]->Option;

	Damage = Monster->Attack - Defense;

	Damage = Damage <= 0 ? 1 : Damage;

	printf("Monster가 Player에게 %d 데미지를 주었습니다.\n", Damage);

	gPlayer->HP -= Damage;

	// 플레이어가 죽었는지 판단한다.
	if (gPlayer->HP <= 0)
	{
		// 플레이어가 죽었을 경우 경험치와 골드를 10% 감소시키고
		// 체력과 마나를 최대치로 하여 부활시킨다.
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

FMonsterInfo* CreateMonster(EMapMenu::Type BattleType)
{
	FMonsterInfo* Monster = new FMonsterInfo;

	int	MenuIndex = BattleType - 1;

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

// 이 cpp에서만 사용할 함수는 헤더에 선언부분이 없어도 된다.
// 단, 이 함수는 이 함수보다 아래에 있는 함수에서 사용할 수 있다.
void RunBattle(EMapMenu::Type BattleType)
{
	// 난이도에 맞는 몬스터를 생성한다.
	FMonsterInfo* Monster = CreateMonster(BattleType);

	while (true)
	{
		system("cls");
		printf("================ Player ================\n");
		OutputPlayerBattle();

		printf("================ Monster ================\n");
		OutputMonsterBattle(Monster);

		// 전투 메뉴
		printf("1. 공격\n");
		printf("2. 도망가기\n");
		printf("메뉴를 선택하세요 : ");
		int	Input;
		scanf_s("%d", &Input);

		if (Input <= EBattleMenu::None ||
			Input >= EBattleMenu::End)
			continue;

		switch (Input)
		{
		case EBattleMenu::Attack:
			if (Battle(Monster) == EBattleResult::MonsterDeath)
			{
				//Monster->HP = Monster->HPMax;
				//Monster->MP = Monster->MPMax;
				// 죽은 몬스터를 제거하고 다시 생성한다.
				SAFE_DELETE(Monster);

				Monster = CreateMonster(BattleType);
			}
			break;
		case EBattleMenu::Back:
			// 여기서 메모리 제거가 없을 경우 메모리 릭이 남게 된다.
			SAFE_DELETE(Monster);
			return;
		}
	}
}

void RunMap()
{
	while (true)
	{
		// 전투 메뉴를 보여주고 선택한다.
		system("cls");
		printf("1. 쉬움\n");
		printf("2. 보통\n");
		printf("3. 어려움\n");
		printf("4. 뒤로가기\n");
		printf("메뉴를 선택하세요 : ");
		int	Input = 0;
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
