
#include "Battle.h"

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

	printf("���� : %d\t����ġ : %d\n", gPlayer->Level, gPlayer->Exp);
	printf("���ݷ� : %d\t���� : %d\n", gPlayer->Attack, gPlayer->Defense);
	printf("ü�� : %d / %d\t���� : %d / %d\n", 
		gPlayer->HP, gPlayer->HPMax, gPlayer->MP, gPlayer->MPMax);
	printf("��� : %d\n", gPlayer->Gold);
}

// ���� ���� ���
void OutputMonsterBattle(FMonsterInfo* Monster)
{
	printf("�̸� : %s\n\t���� : %d\n", Monster->Name, Monster->Level);
	printf("ȹ�� ����ġ : %d\tȹ�� ��� : %d\n", Monster->Exp, Monster->Gold);
	printf("���ݷ� : %d\t���� : %d\n", Monster->Attack, Monster->Defense);
	printf("ü�� : %d / %d\t���� : %d / %d\n",
		Monster->HP, Monster->HPMax, Monster->MP, Monster->MPMax);
}

// ���� ���� �Լ�
void RunBattle(EMapMenu::Type BattleType)
{
	// ���̵��� �´� ���� ����
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

	// ���� ����
	while (true)
	{
		system("cls");

		// �÷��̾�, ���� ���� ���
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

		// ���� �޴� ��� �� ����
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
