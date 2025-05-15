
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

bool BattleInit()
{
	// MonsterInfo ���Ϸκ��� ���� ������ �о �޸𸮿� ����
	FILE* FileStream = nullptr;

	fopen_s(&FileStream, "MonsterInfo.mst", "rb");

	if (!FileStream)
		return false;

	fread(gMonsterOriginInfo, sizeof(FMonsterEditorInfo), EMapMenu::MapCount, FileStream);

	fclose(FileStream);

	return true;
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

	printf("���� : %d\t\t����ġ : %d\n", gPlayer->Level, gPlayer->Exp);
	printf("���ݷ� : %d\t\t���� : %d\n", gPlayer->Attack, gPlayer->Defense);
	printf("ü�� : %d / %d\t���� : %d / %d\n", 
		gPlayer->HP, gPlayer->HPMax, gPlayer->MP, gPlayer->MPMax);
	printf("��� : %d\n", gPlayer->Gold);
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
	int Damage = gPlayer->Attack - Monster->Defense;

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

		system("pause");

		return EBattleResult::MonsterDeath;
	}

	// ���Ͱ� �÷��̾ ����
	Damage = Monster->Attack - gPlayer->Defense;

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
