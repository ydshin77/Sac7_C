
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
	// ���� ���Ϸκ��� ���� ������ �о �޸𸮿� �÷��д�.
	FILE* File = nullptr;

	fopen_s(&File, "MonsterInfo.mst", "rb");

	if (!File)
		return false;

	fread(gMonsterOriginInfo, sizeof(FMonsterEditorInfo),
		EMapMenu::MapCount, File);

	fclose(File);

	// ����ġ ���̺��� �о�´�.
	fopen_s(&File, "ExpTable.txt", "rt");

	if (!File)
		return false;

	char	Line[512] = {};

	fgets(Line, 512, File);

	int	TableCount = atoi(Line);

	gExpTable = new int[TableCount];

	fgets(Line, 512, File);

	// ���ڿ��� �и��Ѵ�.
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
	printf("�̸� : %s\t���� : ", gPlayer->Name);

	switch (gPlayer->Job)
	{
	case EPlayerJob::Knight:
		printf("���\n");
		break;
	case EPlayerJob::Archer:
		printf("�ü�\n");
		break;
	case EPlayerJob::Magicion:
		printf("������\n");
		break;
	}

	printf("���� : %d\t����ġ : %d / %d\n", gPlayer->Level,
		gPlayer->Exp, gExpTable[gPlayer->Level - 1]);
	/*printf("���ݷ� : %d\t���� : %d\n", gPlayer->Attack,
		gPlayer->Defense);*/

	printf("���ݷ� : %d", gPlayer->Attack);

	if (gPlayer->EquipItem[EEquip::Weapon])
		printf(" + %d", gPlayer->EquipItem[EEquip::Weapon]->Option);

	printf("\t���� : %d", gPlayer->Defense);

	if (gPlayer->EquipItem[EEquip::Armor])
		printf(" + %d", gPlayer->EquipItem[EEquip::Armor]->Option);

	printf("\n");

	printf("ü�� : %d / %d\t���� : %d / %d\n",
		gPlayer->HP, gPlayer->HPMax,
		gPlayer->MP, gPlayer->MPMax);
	printf("��� : %d\n", gPlayer->Gold);

	printf("�������� : ");

	if (gPlayer->EquipItem[EEquip::Weapon])
		printf("%s\t", gPlayer->EquipItem[EEquip::Weapon]->Name);

	else
		printf("����\t");

	printf("������ : ");

	if (gPlayer->EquipItem[EEquip::Armor])
		printf("%s\n", gPlayer->EquipItem[EEquip::Armor]->Name);

	else
		printf("����\n");
}

void OutputMonsterBattle(FMonsterInfo* Monster)
{
	printf("�̸� : %s\t���� : %d\n", Monster->Name,
		Monster->Level);

	printf("ȹ�����ġ : %d\tȹ���� : %d\n", Monster->Exp,
		Monster->Gold);
	printf("���ݷ� : %d\t���� : %d\n", Monster->Attack,
		Monster->Defense);
	printf("ü�� : %d / %d\t���� : %d / %d\n",
		Monster->HP, Monster->HPMax,
		Monster->MP, Monster->MPMax);
}

EBattleResult Battle(FMonsterInfo* Monster)
{
	// �÷��̾ ���͸� �����Ѵ�.
	// ���� ���Ⱑ ���� ��� �߰� ���ݷ��� ����Ǿ�� �Ѵ�.
	int	Attack = gPlayer->Attack;

	if (gPlayer->EquipItem[EEquip::Weapon])
		Attack += gPlayer->EquipItem[EEquip::Weapon]->Option;

	int	Damage = Attack - Monster->Defense;

	// �ּҵ������� 1�� �� �� �ְ� �Ѵ�.
	// ���׿����� : ������ ���ǽ��� true�� ��� : ������ ���� ��ȯ�ǰ�
	// false�� ��� : �������� ���� ��ȯ�ȴ�.
	Damage = Damage <= 0 ? 1 : Damage;
	/*if (Damage <= 0)
		Damage = 1;*/

	printf("Player�� Monster���� %d �������� �־����ϴ�.\n", Damage);

	Monster->HP -= Damage;

	// ���Ͱ� �׾����� Ȯ���Ѵ�.
	if (Monster->HP <= 0)
	{
		// ����ġ�� ��带 �����ϰ� �Ѵ�.
		gPlayer->Exp += Monster->Exp;
		gPlayer->Gold += Monster->Gold;

		printf("Monster�� �׾����ϴ�.\n");

		// �κ��丮�� ������ ���� ��쿡�� �������� ȹ���� �� �ְ� �Ѵ�.
		if (gInventory->Count < INVENTORY_MAX)
		{
			// �������� ����� Ȯ���� ���Ѵ�.
			float	Percent = rand() % 10000 / 100.f;

			// 20% Ȯ���� �������� ȹ���Ѵ�.
			if (Percent < 20.f)
			{
				// � �������� ������� �����Ѵ�.
				int	DropIndex = rand() % gItemListCount;

				FItem* DropItem = new FItem;

				*DropItem = gItemList[DropIndex];

				// �κ��丮�� �� ������ ã�� �������� �־��ش�.
				for (int i = 0; i < INVENTORY_MAX; ++i)
				{
					if (!gInventory->ItemList[i])
					{
						gInventory->ItemList[i] = DropItem;
						++gInventory->Count;
						break;
					}
				}

				printf("%s �������� ȹ���Ͽ����ϴ�.\n",
					DropItem->Name);
				system("pause");
			}
		}


		// ������ �ߴ��� Ȯ��.
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

			printf("������ �ö����ϴ�.\n");
		}

		system("pause");

		return EBattleResult::MonsterDeath;
	}

	// ���Ͱ� �÷��̾ �����Ѵ�.
	// �������� ���� ��� �߰� ������ �����Ѵ�.
	int	Defense = gPlayer->Defense;

	if (gPlayer->EquipItem[EEquip::Armor])
		Defense += gPlayer->EquipItem[EEquip::Armor]->Option;

	Damage = Monster->Attack - Defense;

	Damage = Damage <= 0 ? 1 : Damage;

	printf("Monster�� Player���� %d �������� �־����ϴ�.\n", Damage);

	gPlayer->HP -= Damage;

	// �÷��̾ �׾����� �Ǵ��Ѵ�.
	if (gPlayer->HP <= 0)
	{
		// �÷��̾ �׾��� ��� ����ġ�� ��带 10% ���ҽ�Ű��
		// ü�°� ������ �ִ�ġ�� �Ͽ� ��Ȱ��Ų��.
		gPlayer->Exp = (int)(gPlayer->Exp * 0.9f);
		gPlayer->Gold = (int)(gPlayer->Gold * 0.9f);

		gPlayer->HP = gPlayer->HPMax;
		gPlayer->MP = gPlayer->MPMax;

		printf("Player�� �׾����ϴ�.\n");

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

// �� cpp������ ����� �Լ��� ����� ����κ��� ��� �ȴ�.
// ��, �� �Լ��� �� �Լ����� �Ʒ��� �ִ� �Լ����� ����� �� �ִ�.
void RunBattle(EMapMenu::Type BattleType)
{
	// ���̵��� �´� ���͸� �����Ѵ�.
	FMonsterInfo* Monster = CreateMonster(BattleType);

	while (true)
	{
		system("cls");
		printf("================ Player ================\n");
		OutputPlayerBattle();

		printf("================ Monster ================\n");
		OutputMonsterBattle(Monster);

		// ���� �޴�
		printf("1. ����\n");
		printf("2. ��������\n");
		printf("�޴��� �����ϼ��� : ");
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
				// ���� ���͸� �����ϰ� �ٽ� �����Ѵ�.
				SAFE_DELETE(Monster);

				Monster = CreateMonster(BattleType);
			}
			break;
		case EBattleMenu::Back:
			// ���⼭ �޸� ���Ű� ���� ��� �޸� ���� ���� �ȴ�.
			SAFE_DELETE(Monster);
			return;
		}
	}
}

void RunMap()
{
	while (true)
	{
		// ���� �޴��� �����ְ� �����Ѵ�.
		system("cls");
		printf("1. ����\n");
		printf("2. ����\n");
		printf("3. �����\n");
		printf("4. �ڷΰ���\n");
		printf("�޴��� �����ϼ��� : ");
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
