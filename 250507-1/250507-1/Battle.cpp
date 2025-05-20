
#include "Battle.h"

// ���� �޴�
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

// ���� ���
enum class EBattleResult : unsigned char
{
	None,
	PlayerDeath,
	MonsterDeath
};

// ���� �ʱ�ȭ ��, MonsterInfo ���Ͽ��� �о�� ������ ������ �������� ����
FMonsterEditorInfo gMonsterOriginInfo[EMapMenu::MapCount];

// ����ġ ���̺�
int* gExpTable = nullptr;

bool BattleInit()
{
	// MonsterInfo ���Ϸκ��� ���� ������ �о �޸𸮿� ����
	FILE* FileStream = nullptr;

	fopen_s(&FileStream, "MonsterInfo.mst", "rb");

	if (!FileStream)
		return false;

	fread(gMonsterOriginInfo, sizeof(FMonsterEditorInfo), EMapMenu::MapCount, FileStream);

	fclose(FileStream);

	// ����ġ ���̺� �о��
	fopen_s(&FileStream, "ExpTable.txt", "rt");

	if (!FileStream)
		return false;

	char Line[512] = {};

	// ���̺� ���� ���� (ù��°��)
	fgets(Line, 512, FileStream);

	int TableCount = atoi(Line);

	// ����ġ ���̺� ���� �Ҵ�
	gExpTable = new int[TableCount];

	// ���ڿ� �и� (�ι�°��)
	fgets(Line, 512, FileStream);

	char* Context = nullptr;
	char* TokResult = strtok_s(Line, ",", &Context);

	// ����ġ ���̺� �� �ֱ�
	gExpTable[0] = atoi(TokResult);

	for (int i = 1; i < TableCount; ++i)
	{
		TokResult = strtok_s(nullptr, ",", &Context);
		gExpTable[i] = atoi(TokResult);
	}

	fclose(FileStream);

	return true;
}

void BattleDestroy()
{
	SAFE_DELETE_ARRAY(gExpTable);
}

// �÷��̾� ���� ���
// gPlayer�� ��������(extern)�� �����߱� ������ ���ڴ� ���� �ʿ����
void OutputPlayerBattle()
{
	printf("�̸� : %s\t\t���� : ", gPlayer->Name);

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

	printf("���� : %d\t\t����ġ : %d / %d\n",
		gPlayer->Level, gPlayer->Exp, gExpTable[gPlayer->Level - 1]);

	printf("���ݷ� : %d", gPlayer->Attack);

	if (gPlayer->EquipItem[EEquip::Weapon])
		printf(" + %d", gPlayer->EquipItem[EEquip::Weapon]->Option);

	printf("\t\t���� : %d", gPlayer->Defense);

	if (gPlayer->EquipItem[EEquip::Armor])
		printf(" + %d", gPlayer->EquipItem[EEquip::Armor]->Option);

	printf("\n");

	printf("ü�� : %d / %d\t", gPlayer->HP, gPlayer->HPMax);
	printf("���� : %d / %d\n", gPlayer->MP, gPlayer->MPMax);
	printf("��� : %d\n", gPlayer->Gold);

	printf("���� ���� : ");

	if (gPlayer->EquipItem[EEquip::Weapon])
	{
		printf("%s", gPlayer->EquipItem[EEquip::Weapon]->Name);

		if (gPlayer->EquipItem[EEquip::Weapon]->Upgrade > 0)
			printf(" +%d", gPlayer->EquipItem[EEquip::Weapon]->Upgrade);

		printf("\t");
	}

	else
		printf("����\t");

	printf("���� �� : ");
	if (gPlayer->EquipItem[EEquip::Armor])
	{
		printf("%s", gPlayer->EquipItem[EEquip::Armor]->Name);

		if (gPlayer->EquipItem[EEquip::Armor]->Upgrade > 0)
			printf(" +%d", gPlayer->EquipItem[EEquip::Armor]->Upgrade);

		printf("\n");
	}

	else
		printf("����\n");
}

// ���� ���� ���
void OutputMonsterBattle(FMonsterInfo* Monster)
{
	printf("�̸� : %s\t\t���� : %d\n", Monster->Name, Monster->Level);
	printf("���ݷ� : %d\t\t���� : %d\n", Monster->Attack, Monster->Defense);
	printf("ü�� : %d / %d\t���� : %d / %d\n",
		Monster->HP, Monster->HPMax, Monster->MP, Monster->MPMax);
	printf("ȹ�� ����ġ : %d\tȹ�� ��� : %d\n", Monster->Exp, Monster->Gold);
}

// ���� �Լ�
EBattleResult Battle(FMonsterInfo* Monster)
{
	// �÷��̾ ���͸� ����
	// ���� ���Ⱑ ���� ��� �߰� ���ݷ� ����
	int Attack = gPlayer->Attack;

	if (gPlayer->EquipItem[EEquip::Weapon])
		Attack += gPlayer->EquipItem[EEquip::Weapon]->Option;

	int Damage = Attack - Monster->Defense;

	// �������� �ּ� 1�̶� �� �� �ֵ��� ��
	// ��� 1. ���׿����� ���
	Damage = Damage <= 0 ? 1 : Damage;

	printf("Player�� Monster���� %d �������� �־����ϴ�.\n", Damage);

	// ��� 2. if�� ���
	/*if (Damage <= 0)
		Damage = 1;*/

	// ���� ü�� ����
	Monster->HP -= Damage;

	// ���Ͱ� �׾����� Ȯ��
	if (Monster->HP <= 0)
	{
		// ����ġ�� ��� ����
		gPlayer->Exp += Monster->Exp;
		gPlayer->Gold += Monster->Gold;

		printf("Monster�� �׾����ϴ�.\n");

		// �κ��丮�� ������ ���� ��쿡�� ������ ȹ�� ����
		if (gInventory->Count < INVENTORY_MAX)
		{
			// ������ ��� Ȯ�� ���ϱ�
			float Percent = rand() % 10000 / 100.f;

			// 20% Ȯ���� ������ ȹ��
			if (Percent < 20.f)
			{
				// � �������� ������� ����
				int DropIndex = rand() % gItemListCount;

				FItem* DropItem = new FItem;

				*DropItem = gItemList[DropIndex];

				// �κ��丮�� �� ������ ã�� �������� ����
				for (int i = 0; i < INVENTORY_MAX; ++i)
				{
					if (!gInventory->ItemList[i])
					{
						gInventory->ItemList[i] = DropItem;
						++gInventory->Count;
						break;
					}
				}

				printf("%s �������� ȹ���Ͽ����ϴ�.\n", DropItem->Name);
			}
		}

		// ������ �ߴ��� Ȯ��
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

	// ���Ͱ� �÷��̾ ����
	// ���� ���� ���� ��� �߰� ���� ����
	int Defense = gPlayer->Defense;

	if (gPlayer->EquipItem[EEquip::Armor])
		Defense += gPlayer->EquipItem[EEquip::Armor]->Option;

	Damage = Monster->Attack - Defense;

	Damage = Damage <= 0 ? 1 : Damage;

	printf("Monster�� Player���� %d �������� �־����ϴ�.\n", Damage);

	// �÷��̾� ü�� ����
	gPlayer->HP -= Damage;

	// �÷��̾ �׾����� Ȯ��
	if (gPlayer->HP <= 0)
	{
		// �÷��̾ �׾��� ���
		// ����ġ�� ��� 10% ����, ü�°� ������ �ִ�ġ�� �Ͽ� ��Ȱ��Ŵ
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

// ���� ���� �Լ�
FMonsterInfo* CreateMonster(EMapMenu::Type BattleType)
{
	// ���̵��� �´� ���� ����
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

// ���� ���� �Լ�
void RunBattle(EMapMenu::Type BattleType)
{
	// ���� ����
	FMonsterInfo* Monster = CreateMonster(BattleType);

	// ���� ����
	while (true)
	{
		system("cls");

		// �÷��̾�, ���� ���� ���
		printf("================= Player =================\n");
		OutputPlayerBattle();

		printf("================= Monster =================\n");
		OutputMonsterBattle(Monster);

		// ���� �޴�
		printf("1. ����\n");
		printf("2. ��������\n");

		printf("�޴��� �����ϼ��� : ");
		int Input = 0;
		scanf_s("%d", &Input);

		if (Input <= EBattleMenu::None || Input >= EBattleMenu::End)
		{
			printf("�߸��� ���� �Է��Ͽ����ϴ�. �ٽ� �Է����ּ���.");
			system("pause");
			continue;
		}

		switch (Input)
		{
		case EBattleMenu::Attack:
			if (Battle(Monster) == EBattleResult::MonsterDeath)
			{
				// ���Ͱ� �׾��� ��� ���ο� ���� ��ȯ
				// ��� 1. ���� ���͸� �����ϰ� �ٽ� ���� (�Ϲ���)
				SAFE_DELETE(Monster);

				Monster = CreateMonster(BattleType);

				// ��� 2. ü��, ���� ȸ����Ŵ
				/*Monster->HP = Monster->HPMax;
				Monster->MP = Monster->MPMax;*/
			}
			break;
		case EBattleMenu::Back:
			// �޸� ���Ű� ���� ��� �޸� ���� ���� ��
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

		// ��Ʋ �޴� ��� �� ����
		printf("1. ����\n");
		printf("2. ����\n");
		printf("3. �����\n");
		printf("4. �ڷΰ���\n");

		printf("�޴��� �����ϼ��� : ");
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
